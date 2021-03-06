/* Generated By:JavaCC: Do not edit this line. ConfigParserConstants.java */
package org.libconfig.parser;


/**
 * Token literal values and constants.
 * Generated by org.javacc.parser.OtherFilesGen#start()
 */
public interface ConfigParserConstants {

  /** End of File. */
  int EOF = 0;
  /** RegularExpression Id. */
  int SINGLE_LINE_COMMENT = 8;
  /** RegularExpression Id. */
  int FORMAL_COMMENT = 9;
  /** RegularExpression Id. */
  int MULTI_LINE_COMMENT = 10;
  /** RegularExpression Id. */
  int BOOLEAN_TOKEN = 12;
  /** RegularExpression Id. */
  int TRUE_VALUE = 13;
  /** RegularExpression Id. */
  int FALSE_VALUE = 14;
  /** RegularExpression Id. */
  int INTEGER_TOKEN = 15;
  /** RegularExpression Id. */
  int DECIMAL_LITERAL = 16;
  /** RegularExpression Id. */
  int HEX_INTEGER = 17;
  /** RegularExpression Id. */
  int HEX_LITERAL = 18;
  /** RegularExpression Id. */
  int FLOATING_POINT_TOKEN = 19;
  /** RegularExpression Id. */
  int DECIMAL_FLOATING_POINT_TOKEN = 20;
  /** RegularExpression Id. */
  int DECIMAL_EXPONENT = 21;
  /** RegularExpression Id. */
  int STRING_TOKEN = 22;
  /** RegularExpression Id. */
  int NAME_TOKEN = 23;
  /** RegularExpression Id. */
  int NAME_TOKEN_LITERAL = 24;
  /** RegularExpression Id. */
  int ONLY_LETTERS_AND_NUMBERS_AND_UNDERSCORE = 25;
  /** RegularExpression Id. */
  int LPAREN = 26;
  /** RegularExpression Id. */
  int RPAREN = 27;
  /** RegularExpression Id. */
  int LBRACE = 28;
  /** RegularExpression Id. */
  int RBRACE = 29;
  /** RegularExpression Id. */
  int LBRACKET = 30;
  /** RegularExpression Id. */
  int RBRACKET = 31;
  /** RegularExpression Id. */
  int SEMICOLON = 32;
  /** RegularExpression Id. */
  int COLON = 33;
  /** RegularExpression Id. */
  int COMMA = 34;
  /** RegularExpression Id. */
  int EQUALS = 35;

  /** Lexical state. */
  int DEFAULT = 0;
  /** Lexical state. */
  int IN_FORMAL_COMMENT = 1;
  /** Lexical state. */
  int IN_MULTI_LINE_COMMENT = 2;

  /** Literal token values. */
  String[] tokenImage = {
    "<EOF>",
    "\" \"",
    "\"\\t\"",
    "\"\\n\"",
    "\"\\r\"",
    "\"\\f\"",
    "<token of kind 6>",
    "\"/*\"",
    "<SINGLE_LINE_COMMENT>",
    "\"*/\"",
    "\"*/\"",
    "<token of kind 11>",
    "<BOOLEAN_TOKEN>",
    "<TRUE_VALUE>",
    "<FALSE_VALUE>",
    "<INTEGER_TOKEN>",
    "<DECIMAL_LITERAL>",
    "<HEX_INTEGER>",
    "<HEX_LITERAL>",
    "<FLOATING_POINT_TOKEN>",
    "<DECIMAL_FLOATING_POINT_TOKEN>",
    "<DECIMAL_EXPONENT>",
    "<STRING_TOKEN>",
    "<NAME_TOKEN>",
    "<NAME_TOKEN_LITERAL>",
    "<ONLY_LETTERS_AND_NUMBERS_AND_UNDERSCORE>",
    "\"(\"",
    "\")\"",
    "\"{\"",
    "\"}\"",
    "\"[\"",
    "\"]\"",
    "\";\"",
    "\":\"",
    "\",\"",
    "\"=\"",
  };

}
