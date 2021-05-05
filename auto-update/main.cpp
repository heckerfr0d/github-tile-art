#include "../headers/calendar.h"
#include <fstream>
#include <iostream>
#include <git2.h>

std::vector<std::chrono::system_clock::time_point> get_active_dates(Art A)
{
    std::vector<std::vector<std::chrono::system_clock::time_point>> dates = dates_by_weekday();
    std::vector<std::chrono::system_clock::time_point> d;
    for(int i=0; i<7; i++)
        for(int j=0; j<52; j++)
            if(A.a[i][j])
                d.push_back(dates[i][j]);
    std::cout<<"done\n";
    return d;
}

int main()
{
    Config c;
    Art a;
    std::vector<Art> A;
    std::ifstream in("daily.dat", std::ios::binary);
    in.read((char*)&c, sizeof(c));
    while(!in.eof())
    {
        in.read((char*)&a, sizeof(a));
        A.push_back(a);
        std::cout<<"read one arr\n";
    }
    std::cout<<c.cmail<<c.cname<<c.path<<c.url<<c.nc<<std::endl;
    srand(time(0));
    int r = rand()%(A.size());
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<52; j++)
            std::cout<<A[0].a[i][j]<<" ";
        std::cout<<std::endl;
    }
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<52; j++)
            std::cout<<A[r].a[i][j]<<" ";
        std::cout<<std::endl;
    }
    std::vector<std::chrono::system_clock::time_point> dates = get_active_dates(A[r]);
    std::cout<<"next\n";
    git_libgit2_init();
    git_repository *rep = NULL;
    git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
    git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
    std::cout<<"parfectok\n";
    checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE;
    clone_opts.checkout_opts = checkout_opts;
    if (git_clone(&rep, c.url, c.path, &clone_opts) < 0)
        if(git_repository_open(&rep, c.path)<0)
            std::cout<<"open/clone fail\n";
    int n = dates.size();

    for (int i=0; i<n; i++)
    {
        for(int j=0; j<c.nc; j++)
        {
            git_signature *me = NULL;
            git_oid commit_oid, tree_oid;
            git_tree *tree;
            git_index *index;
            git_object *parent = NULL;
            git_reference *ref = NULL;
            git_revparse_ext(&parent, &ref, rep, "HEAD");
            if (git_signature_new(&me, c.cname, c.cmail, std::chrono::duration_cast<std::chrono::seconds>(dates[i].time_since_epoch()).count(), 120+j) < 0)
                std::cout<<"sig fail\n";
            git_repository_index(&index, rep);
            if (git_index_write_tree(&tree_oid, index) < 0)
                std::cout<<"tree fail\n";
            if (git_tree_lookup(&tree, rep, &tree_oid) < 0)
                std::cout<<"otree fail\n";
            if (git_commit_create_v(&commit_oid, rep, "HEAD", me, me, NULL, "just aesthetic commits :v:", tree, parent ? 1 : 0, parent) < 0)
                std::cout<<"commit fail\n";
            git_index_free(index);
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
        std::cout<<"lookup fail\n";
    if (git_push_options_init(&options, GIT_PUSH_OPTIONS_VERSION) < 0)
        std::cout<<"opush fail\n";
    if (git_remote_push(remote, &refspecs, &options) < 0)
        std::cout<<"push fail\n";
    git_remote_free(remote);
    git_repository_free(rep);
    return 0;
}
