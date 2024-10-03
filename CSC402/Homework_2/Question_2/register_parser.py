'''
Parser for our Register language
'''

declared_registers = set()

def prog(stream):
    while stream.pointer().type in ['REGISTER', 'COPY']:
        stmt(stream)
    return

def stmt(stream):
    if stream.pointer().type in ['REGISTER']:
        reg = stream.pointer().value
        stream.match('REGISTER')
        declared_registers.add(reg)  # Add the register to the declared set
        return
    elif stream.pointer().type in ['COPY']:
        stream.match('COPY')
        reg = stream.pointer().value
        exp(stream)
        if reg not in declared_registers:
            raise SyntaxError("stmt: syntax error at {}".format(reg))
        return
    else:
        raise SyntaxError("stmt: syntax error at {}".format(stream.pointer().value))
    
def exp(stream):
    if stream.pointer().type in ['NUMBER']:
        stream.match('NUMBER')
        return
    elif stream.pointer().type in ['PLUS']:
        stream.match('PLUS')
        return
    elif stream.pointer().type in ['MINUS']:
        stream.match('MINUS')
        return
    elif stream.pointer().type in ['MULT']:
        stream.match('MULT')
        return
    elif stream.pointer().type in ['DIV']:
        stream.match('DIV')
        return
    elif stream.pointer().type in ['REGISTER']:
        reg = stream.pointer().value
        if reg not in declared_registers:
            raise SyntaxError("exp: syntax error at {}".format(reg))
        stream.match('REGISTER')
        return
    elif stream.pointer().type in ['LPAREN']:
        stream.match('LPAREN')
        exp(stream)
        stream.match('RPAREN')
        return
    else:
        raise SyntaxError("exp: syntax error at {}".format(stream.pointer().value))


def number(stream):
    if stream.pointer().type in ['NUMBER']:
        stream.match('NUMBER')
        return
    else:
        raise SyntaxError("number: syntax error at {}".format(stream.pointer().value))
        

# parser top-level driver
def parse(char_stream=None):
    from register_lexer import Lexer
    from sys import stdin
    try:
        if not char_stream:
            char_stream = stdin.read() # read from stdin
        token_stream = Lexer(char_stream)
        prog(token_stream) # call the parser function for start symbol
        if token_stream.end_of_file():
            print("parse successful")
        else:
            raise SyntaxError("Incomplete parse: syntax error at {}"
                              .format(token_stream.pointer().value))
    except SyntaxError as e:
        print("error: " + str(e))

if __name__ == "__main__":
    parse()
