'''
Parser for our Exp1 language
'''

# prog : {“”, LPAREN exp RPAREN, VAR, NUM} (sexp)*
def prog(stream):
    while stream.pointer().type in ['LPAREN','VAR','NUM']:
        sexp(stream)
    return

# sexp : {PLUS, MINUS, MULT, DIV, STORE, PRINT} LPAREN exp RPAREN
# | {[a-z],[A-Z],[0-9]} VAR
# | {0, 1, 2, 3, 4, 5, 6, 7, 8, 9} NUM

def sexp(stream):
    if stream.pointer().type in ['LPAREN']:
        stream.match('LPAREN')
        exp(stream)
        stream.match('RPAREN')
        return
    elif stream.pointer().type in ['VAR']:
        var(stream)
        return
    elif stream.pointer().type in ['NUM']:
        num(stream)
        return
    else:
        raise SyntaxError("sexp: syntax error at {}".format(stream.pointer().value))

# exp : {PLUS} PLUS exp exp
#     | {MINUS} MINUS exp exp
#     | {LPAREN} LPAREN exp RPAREN
#     | {NAME} var
#     | {NUMBER} num
def exp(stream):
    token = stream.pointer()
    if token.type in ['PLUS']:
        stream.match('PLUS')
        sexp(stream)
        sexp(stream)
        return
    elif token.type in ['MINUS']:
        stream.match('MINUS')
        sexp(stream)
        sexp(stream)
        return
    elif token.type in ['MULT']:
        stream.match('MULT')
        sexp(stream)
        sexp(stream)
        return
    elif token.type in ['DIV']:
        stream.match('DIV')
        sexp(stream)
        sexp(stream)
        return
    elif token.type in ['STORE']:
        stream.match('STORE')
        var(stream)
        sexp(stream)
        return
    elif token.type in ['PRINT']:
        stream.match('PRINT')
        sexp(stream)
        return
    else:
        raise SyntaxError("exp: syntax error at {}".format(token.value))

# var : {NAME} NAME
def var(stream):
    token = stream.pointer()
    if token.type in ['VAR']:
        stream.match('VAR')
        return
    else:
        raise SyntaxError("var: syntax error at {}".format(token.value))

# num : {NUMBER} NUMBER
def num(stream):
    token = stream.pointer()
    if token.type in ['NUM']:
        stream.match('NUM')
        return
    else:
        raise SyntaxError("num: syntax error at {}".format(token.value))

# parser top-level driver
def parse(char_stream=None):
    from exp1_lexer import Lexer
    from sys import stdin
    try:
        if not char_stream:
            char_stream = stdin.read() # read from stdin
        token_stream = Lexer(char_stream)
        prog(token_stream) # call the parser function for start symbol
        if token_stream.end_of_file():
            print("parse successful")
        else:
            raise SyntaxError("parse: syntax error at {}"
                              .format(token_stream.pointer().value))
    except Exception as e:
        print("error: " + str(e))

if __name__ == "__main__":
    parse()
