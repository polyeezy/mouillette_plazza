//
// Parser.cpp for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/src
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Fri Feb 12 03:01:42 2016 Valerian Polizzi
// Last update Tue Apr 19 11:13:42 2016 Valerian Polizzi
//

#include <CommandParser.hh>
# include <fstream>

CommandParser::CommandParser() : _line("0"), _lex("misc/lex/command.lex")
{
  //  this->_fcn.push_back(&CommandParser::createTrue);
}

CommandParser::~CommandParser()
{
}

void		CommandParser::feed(const std::string &input)
{
  std::stringstream	content(input);
  std::string		file("");

  std::string		toget("");
  //  int			token_id(0);

  if (input.size() == 0)
    throw plazza::Exception("[plazza] Syntax error : Empty input (line " + this->_line + ")");
  content >> file;		// FIRST PARAM MUST BE A FILE

  if (this->_lex.lex_line(file) == 1 || this->_lex.lex_line(file) == -1)
    throw plazza::Exception("[plazza] Syntax error : First parameter must be a file (line " + this->_line + ")");
  while (content >> toget)
    {
      if (this->_lex.lex_line(toget) == 1)
	content >> toget;
    }
  // if (this->_lex.lex_line(toget) != 1)
  // throw plazza::Exception("[plazza] Syntax error : Last parameter must be like : '*_*'   (line " + this->_line + ")");
  std::cout << file << " |  " << toget << std::endl;
}

std::string	epur_alpha(std::string str)
{
  size_t i = 0;
  size_t len = str.length();
  while(i < len)
    {
      if (!isalnum(str[i]))
	{
	str.erase(i,1);
	len--;
      }
      else
	i++;
    }
  return (str);
}

const Lexer		&CommandParser::getLexer()
{
  return (_lex);
}

int		CommandParser::check_cmd(const std::string &line)
{
  int		token_id = this->_lex.lex_line(line);

  if (token_id == -1)
    throw plazza::Exception("[PLAZZA] Parse Error : unknown command : '" + line + "' (line " + this->_line + ")");
  return (token_id);
}

void		CommandParser::incr_line(void)
{
  this->_line = std::to_string(atoi(this->_line.c_str()) + 1);
}