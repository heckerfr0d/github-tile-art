#include "../headers/calendar.h"
#include <fstream>
#include <string.h>
#include <git2.h>

std::vector<std::chrono::system_clock::time_point> get_active_dates(Art A)
{
    std::vector<std::vector<std::chrono::system_clock::time_point>> dates = dates_by_weekday();
    std::vector<std::chrono::system_clock::time_point> d;
    for(int i=0; i<52; i++)
        for(int j=0; j<7; j++)
            if(A.a[j][i])
                d.push_back(dates[j][i]);
    return d;
}

int main()
{
    Config c;
    Art a;
    std::vector<Art> A;
    std::ifstream in("config.bin", std::ios::binary);
    in.read((char*)&c, sizeof(c));
    while(!in.eof())
    {
        in.read((char*)&a, sizeof(a));
        A.push_back(a);
    }
    srand(time(0));
    int r = rand()%(A.size());
    std::vector<std::chrono::system_clock::time_point> dates = get_active_dates(A[r]);
    char curl[200] = "curl -X DELETE -H \"Authorization: token ";
    strcat(curl, c.auth);
    strcat(curl, "\" https://api.github.com/repos/");
    strcat(curl, c.cname);
    strcat(curl, "/");
    strcat(curl, c.path);
    system(curl);
    strcpy(curl, "curl -i -H \"Authorization: token ");
    strcat(curl, c.auth);
    strcat(curl, "\" -d \"{\\\"name\\\":\\\"");
    strcat(curl, c.path);
    strcat(curl, "\\\",\\\"description\\\":\\\"A repo for GitHub graffiti\\\"}\" https://api.github.com/user/repos");
    system(curl);
    git_libgit2_init();
    git_repository *rep = NULL;
    git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
    git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
    checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE;
    clone_opts.checkout_opts = checkout_opts;
    if (git_clone(&rep, c.url, c.path, &clone_opts) < 0)
        if(git_repository_open(&rep, c.path)<0)
            return -1;
    int n = dates.size();
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<A[r].nc; j++)
        {
            git_signature *me = NULL;
            git_oid commit_oid, tree_oid;
            git_tree *tree;
            git_index *index;
            git_object *parent = NULL;
            git_reference *ref = NULL;
            git_revparse_ext(&parent, &ref, rep, "HEAD");
            if (git_signature_new(&me, c.cname, c.cmail, std::chrono::duration_cast<std::chrono::seconds>(dates[i].time_since_epoch()).count()+j*10, 330) < 0)
                return -2;
            git_repository_index(&index, rep);
            if (git_index_write_tree(&tree_oid, index) < 0)
                return -3;
            git_index_free(index);
            if (git_tree_lookup(&tree, rep, &tree_oid) < 0)
                return -4;
            if (git_commit_create_v(&commit_oid, rep, "HEAD", me, me, NULL, "just aesthetic commits :v:", tree, parent ? 1 : 0, parent) < 0)
                return -5;
            git_signature_free(me);
            git_tree_free(tree);
            git_object_free(parent);
            git_reference_free(ref);
        }
    }
    git_push_options options;
    git_remote *remote = NULL;
    char *refspec = "refs/heads/master";
    const git_strarray refspecs = {
        &refspec,
        1};
    if (git_remote_lookup(&remote, rep, "origin") < 0)
        return -7;
    if (git_push_options_init(&options, GIT_PUSH_OPTIONS_VERSION) < 0)
        return -8;
    if (git_remote_push(remote, &refspecs, &options) < 0)
        return -9;
    git_remote_free(remote);
    git_repository_free(rep);
    strcpy(curl, "rmdir /s /Q ");
    strcat(curl, c.path);
    system(curl);
    return 0;
}
