#ifndef FONT_H
#define FONT_H

#include <vector>
#include <unordered_map>
#include <string>


//  initialize a dictionary that maps characters to matrices
std::unordered_map<char, std::vector<std::string>> init()
{
    std::unordered_map<char, std::vector<std::string>> txt;
    txt['a'].push_back("    ");
    txt['a'].push_back(" aa ");
    txt['a'].push_back("a  a");
    txt['a'].push_back("aaaa");
    txt['a'].push_back("a  a");
    txt['a'].push_back("a  a");
    txt['a'].push_back("    ");

    txt['b'].push_back("    ");
    txt['b'].push_back("bbb ");
    txt['b'].push_back("b  b");
    txt['b'].push_back("bbbb");
    txt['b'].push_back("b  b");
    txt['b'].push_back("bbb ");
    txt['b'].push_back("    ");

    txt['c'].push_back("    ");
    txt['c'].push_back(" cc ");
    txt['c'].push_back("c  c");
    txt['c'].push_back("c   ");
    txt['c'].push_back("c  c");
    txt['c'].push_back(" cc ");
    txt['c'].push_back("    ");

    txt['d'].push_back("    ");
    txt['d'].push_back("ddd ");
    txt['d'].push_back("d  d");
    txt['d'].push_back("d  d");
    txt['d'].push_back("d  d");
    txt['d'].push_back("ddd ");
    txt['d'].push_back("    ");

    txt['e'].push_back("   ");
    txt['e'].push_back("eee");
    txt['e'].push_back("e  ");
    txt['e'].push_back("eee");
    txt['e'].push_back("e  ");
    txt['e'].push_back("eee");
    txt['e'].push_back("   ");

    txt['f'].push_back("   ");
    txt['f'].push_back("fff");
    txt['f'].push_back("f  ");
    txt['f'].push_back("fff");
    txt['f'].push_back("f  ");
    txt['f'].push_back("f  ");
    txt['f'].push_back("   ");

    txt['g'].push_back("    ");
    txt['g'].push_back(" ggg");
    txt['g'].push_back("g   ");
    txt['g'].push_back("g gg");
    txt['g'].push_back("g  g");
    txt['g'].push_back(" gg ");
    txt['g'].push_back("    ");

    txt['h'].push_back("    ");
    txt['h'].push_back("h  h");
    txt['h'].push_back("h  h");
    txt['h'].push_back("hhhh");
    txt['h'].push_back("h  h");
    txt['h'].push_back("h  h");
    txt['h'].push_back("    ");

    txt['i'].push_back(" ");
    txt['i'].push_back("i");
    txt['i'].push_back("i");
    txt['i'].push_back("i");
    txt['i'].push_back("i");
    txt['i'].push_back("i");
    txt['i'].push_back(" ");

    txt['j'].push_back("    ");
    txt['j'].push_back("   j");
    txt['j'].push_back("   j");
    txt['j'].push_back("   j");
    txt['j'].push_back("j  j");
    txt['j'].push_back(" jj ");
    txt['j'].push_back("    ");

    txt['k'].push_back("    ");
    txt['k'].push_back("k  k");
    txt['k'].push_back("k k ");
    txt['k'].push_back("kk  ");
    txt['k'].push_back("k k ");
    txt['k'].push_back("k  k");
    txt['k'].push_back("    ");

    txt['l'].push_back("   ");
    txt['l'].push_back("l  ");
    txt['l'].push_back("l  ");
    txt['l'].push_back("l  ");
    txt['l'].push_back("l  ");
    txt['l'].push_back("lll");
    txt['l'].push_back("   ");

    txt['m'].push_back("     ");
    txt['m'].push_back("m   m");
    txt['m'].push_back("mm mm");
    txt['m'].push_back("m m m");
    txt['m'].push_back("m   m");
    txt['m'].push_back("m   m");
    txt['m'].push_back("     ");

    txt['n'].push_back("     ");
    txt['n'].push_back("n   n");
    txt['n'].push_back("nn  n");
    txt['n'].push_back("n n n");
    txt['n'].push_back("n  nn");
    txt['n'].push_back("n   n");
    txt['n'].push_back("     ");

    txt['o'].push_back("    ");
    txt['o'].push_back(" oo ");
    txt['o'].push_back("o  o");
    txt['o'].push_back("o  o");
    txt['o'].push_back("o  o");
    txt['o'].push_back(" oo ");
    txt['o'].push_back("    ");

    txt['p'].push_back("    ");
    txt['p'].push_back("ppp ");
    txt['p'].push_back("p  p");
    txt['p'].push_back("ppp ");
    txt['p'].push_back("p   ");
    txt['p'].push_back("p   ");
    txt['p'].push_back("    ");

    txt['q'].push_back("    ");
    txt['q'].push_back(" qq ");
    txt['q'].push_back("q  q");
    txt['q'].push_back("q  q");
    txt['q'].push_back("q  q");
    txt['q'].push_back(" qq ");
    txt['q'].push_back("   q");

    txt['r'].push_back("    ");
    txt['r'].push_back("rrr ");
    txt['r'].push_back("r  r");
    txt['r'].push_back("rrr ");
    txt['r'].push_back("r r ");
    txt['r'].push_back("r  r");
    txt['r'].push_back("    ");

    txt['s'].push_back("    ");
    txt['s'].push_back(" sss");
    txt['s'].push_back("s   ");
    txt['s'].push_back(" ss ");
    txt['s'].push_back("   s");
    txt['s'].push_back("sss ");
    txt['s'].push_back("    ");

    txt['t'].push_back("   ");
    txt['t'].push_back("ttt");
    txt['t'].push_back(" t ");
    txt['t'].push_back(" t ");
    txt['t'].push_back(" t ");
    txt['t'].push_back(" t ");
    txt['t'].push_back("   ");

    txt['u'].push_back("    ");
    txt['u'].push_back("u  u");
    txt['u'].push_back("u  u");
    txt['u'].push_back("u  u");
    txt['u'].push_back("u  u");
    txt['u'].push_back(" uu ");
    txt['u'].push_back("    ");

    txt['v'].push_back("     ");
    txt['v'].push_back("v   v");
    txt['v'].push_back("v   v");
    txt['v'].push_back(" v v ");
    txt['v'].push_back(" v v ");
    txt['v'].push_back("  v  ");
    txt['v'].push_back("     ");

    txt['w'].push_back("     ");
    txt['w'].push_back("w   w");
    txt['w'].push_back("w w w");
    txt['w'].push_back("w w w");
    txt['w'].push_back("w w w");
    txt['w'].push_back(" w w ");
    txt['w'].push_back("     ");

    txt['x'].push_back("     ");
    txt['x'].push_back("x   x");
    txt['x'].push_back(" x x ");
    txt['x'].push_back("  x  ");
    txt['x'].push_back(" x x ");
    txt['x'].push_back("x   x");
    txt['x'].push_back("     ");

    txt['y'].push_back("     ");
    txt['y'].push_back("y   y");
    txt['y'].push_back(" y y ");
    txt['y'].push_back("  y  ");
    txt['y'].push_back("  y  ");
    txt['y'].push_back("  y  ");
    txt['y'].push_back("     ");

    txt['z'].push_back("   ");
    txt['z'].push_back("zzz");
    txt['z'].push_back("  z");
    txt['z'].push_back(" z ");
    txt['z'].push_back("z  ");
    txt['z'].push_back("zzz");
    txt['z'].push_back("   ");

    txt['.'].push_back(" ");
    txt['.'].push_back(" ");
    txt['.'].push_back(" ");
    txt['.'].push_back(" ");
    txt['.'].push_back(" ");
    txt['.'].push_back(".");
    txt['.'].push_back(" ");

    txt[','].push_back("  ");
    txt[','].push_back("  ");
    txt[','].push_back("  ");
    txt[','].push_back("  ");
    txt[','].push_back("  ");
    txt[','].push_back(" ,");
    txt[','].push_back(", ");

    txt[';'].push_back("  ");
    txt[';'].push_back("  ");
    txt[';'].push_back(" ;");
    txt[';'].push_back("  ");
    txt[';'].push_back(" ;");
    txt[';'].push_back("; ");
    txt[';'].push_back("  ");

    txt[':'].push_back(" ");
    txt[':'].push_back(" ");
    txt[':'].push_back(":");
    txt[':'].push_back(" ");
    txt[':'].push_back(":");
    txt[':'].push_back(" ");
    txt[':'].push_back(" ");

    txt['('].push_back("  ");
    txt['('].push_back(" (");
    txt['('].push_back("( ");
    txt['('].push_back("( ");
    txt['('].push_back("( ");
    txt['('].push_back(" (");
    txt['('].push_back("  ");

    txt[')'].push_back("  ");
    txt[')'].push_back(") ");
    txt[')'].push_back(" )");
    txt[')'].push_back(" )");
    txt[')'].push_back(" )");
    txt[')'].push_back(") ");
    txt[')'].push_back("  ");

    txt['{'].push_back("  ");
    txt['{'].push_back("{{");
    txt['{'].push_back("{ ");
    txt['{'].push_back("{ ");
    txt['{'].push_back("{ ");
    txt['{'].push_back("{{");
    txt['{'].push_back("  ");

    txt['}'].push_back("  ");
    txt['}'].push_back("}}");
    txt['}'].push_back(" }");
    txt['}'].push_back(" }");
    txt['}'].push_back(" }");
    txt['}'].push_back("}}");
    txt['}'].push_back("  ");

    txt['<'].push_back("   ");
    txt['<'].push_back("  <");
    txt['<'].push_back(" < ");
    txt['<'].push_back("<  ");
    txt['<'].push_back(" < ");
    txt['<'].push_back("  <");
    txt['<'].push_back("   ");

    txt['>'].push_back("   ");
    txt['>'].push_back(">  ");
    txt['>'].push_back(" > ");
    txt['>'].push_back("  >");
    txt['>'].push_back(" > ");
    txt['>'].push_back(">  ");
    txt['>'].push_back("   ");

    txt['!'].push_back(" ");
    txt['!'].push_back("!");
    txt['!'].push_back("!");
    txt['!'].push_back("!");
    txt['!'].push_back(" ");
    txt['!'].push_back("!");
    txt['!'].push_back(" ");

    txt['?'].push_back("    ");
    txt['?'].push_back("??? ");
    txt['?'].push_back("   ?");
    txt['?'].push_back(" ?? ");
    txt['?'].push_back("    ");
    txt['?'].push_back(" ?  ");
    txt['?'].push_back("    ");

    txt['+'].push_back("     ");
    txt['+'].push_back("  +  ");
    txt['+'].push_back("  +  ");
    txt['+'].push_back("+++++");
    txt['+'].push_back("  +  ");
    txt['+'].push_back("  +  ");
    txt['+'].push_back("     ");

    txt['-'].push_back("   ");
    txt['-'].push_back("   ");
    txt['-'].push_back("   ");
    txt['-'].push_back("---");
    txt['-'].push_back("   ");
    txt['-'].push_back("   ");
    txt['-'].push_back("   ");

    txt['_'].push_back("   ");
    txt['_'].push_back("   ");
    txt['_'].push_back("   ");
    txt['_'].push_back("   ");
    txt['_'].push_back("   ");
    txt['_'].push_back("___");
    txt['_'].push_back("   ");

    txt['*'].push_back("     ");
    txt['*'].push_back("  *  ");
    txt['*'].push_back("* * *");
    txt['*'].push_back(" *** ");
    txt['*'].push_back("* * *");
    txt['*'].push_back("  *  ");
    txt['*'].push_back("     ");

    txt['\''].push_back(" ");
    txt['\''].push_back("'");
    txt['\''].push_back("'");
    txt['\''].push_back(" ");
    txt['\''].push_back(" ");
    txt['\''].push_back(" ");
    txt['\''].push_back(" ");

    txt[' '].push_back(" ");
    txt[' '].push_back(" ");
    txt[' '].push_back(" ");
    txt[' '].push_back(" ");
    txt[' '].push_back(" ");
    txt[' '].push_back(" ");
    txt[' '].push_back(" ");
    return txt;
}


//  get the width of a character matrix
int getwidth(std::vector<std::string> s)
{
    int n = s.size(), m = 0;
    for(int i=0; i<n; i++)
        m = std::max(m, static_cast<int>(s[i].length()));
    return m;
}

#endif // FONT_H
