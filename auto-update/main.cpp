#include "../headers/calendar.h"
#include <fstream>
#include <unistd.h>
#include <algorithm>
#include <string.h>
#include <git2.h>


//  get active dates from Art matrix
std::vector<std::chrono::system_clock::time_point> get_active_dates(Art A)
{
    std::vector<std::vector<std::chrono::system_clock::time_point>> dates;
    if(A.year==-1)
        dates = dates_by_weekday();
    else
        dates = dates_by_weekday(A.year);
    std::vector<std::chrono::system_clock::time_point> d;
    for(int i=0; i<52; i++)
        for(int j=0; j<7; j++)
            if(A.a[j][i])
                d.push_back(dates[j][i]);
    return d;
}

//  make commits in repo given Config and Art
int makeCommits(Config c, Art a)
{
    //  init git stuf
    git_repository *rep = NULL;
    git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
    git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
    checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE;
    clone_opts.checkout_opts = checkout_opts;

    //  git clone
    if (git_clone(&rep, c.url, c.path, &clone_opts) < 0)
        if(git_repository_open(&rep, c.path)<0)
            return -1;
    std::vector<std::chrono::system_clock::time_point> dates = get_active_dates(a);
    for (auto date : dates)
    {
        for(int j=0; j<a.nc; j++)
        {
            git_signature *me = NULL;
            git_oid commit_oid, tree_oid;
            git_tree *tree;
            git_index *index;
            git_object *parent = NULL;
            git_reference *ref = NULL;

            //  get parent commit
            git_revparse_ext(&parent, &ref, rep, "HEAD");

            //  create signature with date
            if (git_signature_new(&me, c.cname, c.cmail, std::chrono::duration_cast<std::chrono::seconds>(date.time_since_epoch()).count()+j*10, 330) < 0)
                return -2;

            //  get index, tree id
            git_repository_index(&index, rep);
            if (git_index_write_tree(&tree_oid, index) < 0)
                return -3;
            git_index_free(index);

            //  get tree from tree id
            if (git_tree_lookup(&tree, rep, &tree_oid) < 0)
                return -4;

            //  git commit (empty)
            if (git_commit_create_v(&commit_oid, rep, "HEAD", me, me, NULL, "just aesthetic commits :v:", tree, parent ? 1 : 0, parent) < 0)
                return -5;

            //  free git stuf
            git_signature_free(me);
            git_tree_free(tree);
            git_object_free(parent);
            git_reference_free(ref);
        }
    }

    //  init git remote stuf
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

    //  git push
    if (git_remote_push(remote, &refspecs, &options) < 0)
        return -9;

    //  free remote git stuf
    git_remote_free(remote);
    git_repository_free(rep);
    return 0;
}

int main()
{
    Config c;
    Art a;
    std::vector<Art> A, A2;
    chdir(getenv("HOME"));
    //  read file
    std::ifstream in("Documents/.config.bin", std::ios::binary);
    in.read((char*)&c, sizeof(c));
    while(!in.eof())
    {
        in.read((char*)&a, sizeof(a));
        if(a.year==-1)
            A.push_back(a);
        else
            A2.push_back(a);
    }
    in.close();
    char repname[50];
    strncat(repname, c.path+10, 50);
    //  delete remote repo using curl
    char curl[200] = "curl -X DELETE -H \"Authorization: token ";
    strcat(curl, c.auth);
    strcat(curl, "\" https://api.github.com/repos/");
    strcat(curl, c.cname);
    strcat(curl, "/");
    strcat(curl, repname);
    system(curl);

    //  create the repo using curl
    strcpy(curl, "curl -i -H \"Authorization: token ");
    strcat(curl, c.auth);
    strcat(curl, "\" -d '{\"name\":\"");
    strcat(curl, repname);
    strcat(curl, "\",\"description\":\"A repo for GitHub graffiti\"}' https://api.github.com/user/repos");
    system(curl);

    git_libgit2_init();

    //  make commits
    for(auto it : A2)
        makeCommits(c, it);
    srand(time(0));
    int r = rand()%(A.size());
    makeCommits(c, A[r]);

    //  clean up
    strcpy(curl, "rm -rf ");
    strcat(curl, c.path);
    system(curl);

    return 0;
}
