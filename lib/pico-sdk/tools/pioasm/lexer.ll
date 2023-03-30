/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <cstring>
# include <string>
# include "pio_assembler.h"
# include "parser.hpp"

#ifdef _MSC_VER
#pragma warning(disable : 4996) // fopen
#endif

%}

%option noyywrap nounput noinput batch debug never-interactive case-insensitive noline

%{
  yy::parser::symbol_type make_INT(const std::string &s, const yy::parser::location_type& loc);
  yy::parser::symbol_type make_HEX(const std::string &s, const yy::parser::location_type& loc);
  yy::parser::symbol_type make_BINARY(const std::string &s, const yy::parser::location_type& loc);
%}

blank         [ \t\r]
whitesp       {blank}+

comment       (";"|"//")[^\n]*

digit         [0-9]
id            [a-zA-Z_][a-zA-Z0-9_]*

binary        "0b"[01]+
int           {digit}+
hex	          "0x"[0-9a-fA-F]+
directive     \.{id}

output_fmt    [^%\n]+

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}

%x code_block
%x c_comment
%x lang_opt

%%
        std::string code_block_contents;
        yy::location code_block_start;
%{
  // A handy shortcut to the location held by the pio_assembler.
  yy::location& loc = pioasm.location;
  // Code run each time yylex is called.
  loc.step();
%}

{blank}+                            loc.step();
\n+                                 { auto loc_newline = loc; loc_newline.end = loc_newline.begin; loc.lines(yyleng); loc.step(); return yy::parser::make_NEWLINE(loc_newline); }

"%"{blank}*{output_fmt}{blank}*"{"  {
                                        BEGIN(code_block);
                                        code_block_contents = "";
                                        code_block_start = loc;
                                        std::string tmp(yytext);
                                        tmp = tmp.substr(1, tmp.length() - 2);
                                        tmp = tmp.erase(0, tmp.find_first_not_of(" \t"));
                                        tmp = tmp.erase(tmp.find_last_not_of(" \t") + 1);
                                        return yy::parser::make_CODE_BLOCK_START( tmp, loc);
                                    }
<code_block>{
    {blank}+                        loc.step();
    \n+                             { auto loc_newline = loc; loc_newline.end = loc_newline.begin; loc.lines(yyleng); loc.step(); }
    "%}"{blank}*                    { BEGIN(INITIAL); auto loc2 = loc; loc2.begin = code_block_start.begin; return yy::parser::make_CODE_BLOCK_CONTENTS(code_block_contents, loc2); }
    .*                              { code_block_contents += std::string(yytext) + "\n"; }
}

<c_comment>{
    {blank}+                        loc.step();
    "*/"                            { BEGIN(INITIAL); }
    "*"                             { }
    [^\n\*]*                        { }
    \n+                             { auto loc_newline = loc; loc_newline.end = loc_newline.begin; loc.lines(yyleng); loc.step(); }
}

<lang_opt>{
\"[^\n]*\"                          return yy::parser::make_STRING(yytext, loc);
{blank}+                            loc.step();
"="		                            return yy::parser::make_EQUAL(loc);
{int}                               return make_INT(yytext, loc);
{hex}                               return make_HEX(yytext, loc);
{binary}                            return make_BINARY(yytext, loc);
[^ \t\n\"=]+                         return yy::parser::make_NON_WS(yytext, loc);
\n+                                 { BEGIN(INITIAL); auto loc_newline = loc; loc_newline.end = loc_newline.begin; loc.lines(yyleng); loc.step(); return yy::parser::make_NEWLINE(loc_newline);  }
.                                   { throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext)); }
}

"/*"                                { BEGIN(c_comment); }
","	                                return yy::parser::make_COMMA(loc);
"::"                                return yy::parser::make_REVERSE(loc);
":"	                                return yy::parser::make_COLON(loc);
"["                                 return yy::parser::make_LBRACKET(loc);
"]"                                 return yy::parser::make_RBRACKET(loc);
"("                                 return yy::parser::make_LPAREN(loc);
")"                                 return yy::parser::make_RPAREN(loc);
"+"                                 return yy::parser::make_PLUS(loc);
"--"                                return yy::parser::make_POST_DECREMENT(loc);
"−−"                                return yy::parser::make_POST_DECREMENT(loc);
"-"                                 return yy::parser::make_MINUS(loc);
"*"                                 return yy::parser::make_MULTIPLY(loc);
"/"                                 return yy::parser::make_DIVIDE(loc);
"|"                                 return yy::parser::make_OR(loc);
"&"                                 return yy::parser::make_AND(loc);
"^"                                 return yy::parser::make_XOR(loc);
"!="		                        return yy::parser::make_NOT_EQUAL(loc);
"!"			                        return yy::parser::make_NOT(loc);
"~"			                        return yy::parser::make_NOT(loc);

".program"		                    return yy::parser::make_PROGRAM(loc);
".wrap_target"	                    return yy::parser::make_WRAP_TARGET(loc);
".wrap"			                    return yy::parser::make_WRAP(loc);
".word"			                    return yy::parser::make_WORD(loc);
".define"		                    return yy::parser::make_DEFINE(loc);
".side_set"		                    return yy::parser::make_SIDE_SET(loc);
".origin"		                    return yy::parser::make_ORIGIN(loc);
".lang_opt"         	            { BEGIN(lang_opt); return yy::parser::make_LANG_OPT(loc); }
{directive}                         return yy::parser::make_UNKNOWN_DIRECTIVE(yytext, loc);

"JMP"			                    return yy::parser::make_JMP(loc);
"WAIT"			                    return yy::parser::make_WAIT(loc);
"IN"			                    return yy::parser::make_IN(loc);
"OUT"			                    return yy::parser::make_OUT(loc);
"PUSH"			                    return yy::parser::make_PUSH(loc);
"PULL"			                    return yy::parser::make_PULL(loc);
"MOV"			                    return yy::parser::make_MOV(loc);
"IRQ"			                    return yy::parser::make_IRQ(loc);
"SET"			                    return yy::parser::make_SET(loc);
"NOP"			                    return yy::parser::make_NOP(loc);

"PUBLIC"		                    return yy::parser::make_PUBLIC(loc);

"OPTIONAL"		                    return yy::parser::make_OPTIONAL(loc);
"OPT"			                    return yy::parser::make_OPTIONAL(loc);
"SIDE"			                    return yy::parser::make_SIDE(loc);
"SIDESET"	                        return yy::parser::make_SIDE(loc);
"SIDE_SET"   	                    return yy::parser::make_SIDE(loc);
"PIN"			                    return yy::parser::make_PIN(loc);
"GPIO"			                    return yy::parser::make_GPIO(loc);
"OSRE"			                    return yy::parser::make_OSRE(loc);

"PINS"			                    return yy::parser::make_PINS(loc);
"NULL"			                    return yy::parser::make_NULL(loc);
"PINDIRS"		                    return yy::parser::make_PINDIRS(loc);
"X"	    		                    return yy::parser::make_X(loc);
"Y"		    	                    return yy::parser::make_Y(loc);
"PC"			                    return yy::parser::make_PC(loc);
"EXEC"			                    return yy::parser::make_EXEC(loc);
"ISR"			                    return yy::parser::make_ISR(loc);
"OSR"			                    return yy::parser::make_OSR(loc);
"STATUS"		                    return yy::parser::make_STATUS(loc);

"BLOCK"			                    return yy::parser::make_BLOCK(loc);
"NOBLOCK"		                    return yy::parser::make_NOBLOCK(loc);
"IFFULL"		                    return yy::parser::make_IFFULL(loc);
"IFEMPTY"		                    return yy::parser::make_IFEMPTY(loc);
"REL"			                    return yy::parser::make_REL(loc);

"CLEAR"			                    return yy::parser::make_CLEAR(loc);
"NOWAIT"		                    return yy::parser::make_NOWAIT(loc);

"ONE"                               return yy::parser::make_INT(1, loc);
"ZERO"                              return yy::parser::make_INT(0, loc);

<<EOF>>                             return yy::parser::make_END(loc);

{int}                               return make_INT(yytext, loc);
{hex}                               return make_HEX(yytext, loc);
{binary}                            return make_BINARY(yytext, loc);

{id}                                return yy::parser::make_ID(yytext, loc);

{comment}                           { }

.                                   { throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext)); }

%%

yy::parser::symbol_type make_INT(const std::string &s, const yy::parser::location_type& loc)
{
  errno = 0;
  long n = strtol (s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "integer is out of range: " + s);
  return yy::parser::make_INT((int) n, loc);
}

yy::parser::symbol_type make_HEX(const std::string &s, const yy::parser::location_type& loc)
{
  errno = 0;
  long n = strtol (s.c_str() + 2, NULL, 16);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "hex is out of range: " + s);
  return yy::parser::make_INT((int) n, loc);
}

yy::parser::symbol_type make_BINARY(const std::string &s, const yy::parser::location_type& loc)
{
  errno = 0;
  long n = strtol (s.c_str()+2, NULL, 2);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "binary is out of range: " + s);
  return yy::parser::make_INT((int) n, loc);
}

void pio_assembler::scan_begin ()
{
  yy_flex_debug = false;
  if (source.empty () || source == "-")
    yyin = stdin;
  else if (!(yyin = fopen (source.c_str (), "r")))
    {
      std::cerr << "cannot open " << source << ": " << strerror(errno) << '\n';
      exit (EXIT_FAILURE);
    }
}

void pio_assembler::scan_end ()
{
  fclose (yyin);
}
