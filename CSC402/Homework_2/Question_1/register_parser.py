'''
Parser for our Register language
'''

# Initialize a set to keep track of declared registers
declared_registers = set()

# prog : (stmt)*
def prog(stream):
    while stream.pointer().type in ['REGISTER', 'COPY']:
        stmt(stream)
    return


# stmt : register <<< exp
#      | <<< register
def stmt(stream):
    if stream.pointer().type in ['REGISTER']:
        reg = stream.pointer().value
        register(stream)
        stream.match('COPY')
        exp(stream)
        declared_registers.add(reg)  # Add the register to the declared set
        return
    elif stream.pointer().type in ['COPY']:
        stream.match('COPY')
        reg = stream.pointer().value
        if reg not in declared_registers:
            raise SyntaxError("stmt: syntax error at {}".format(reg))
        register(stream)
        return
    else:
        raise SyntaxError("stmt: syntax error at {}".format(stream.pointer().value))
# exp : number
#     | register (op register)? -- optional operator clause
def exp(stream):
    if stream.pointer().type in ['NUMBER']:
        number(stream)
        return
    elif stream.pointer().type in ['REGISTER']:
        reg = stream.pointer().value
        if reg not in declared_registers:
            raise SyntaxError("exp: syntax error at {}".format(reg))
        register(stream)
        if stream.pointer().type in ['PLUS','MINUS','MULT','DIV']:
            op(stream)
            reg = stream.pointer().value
            if reg not in declared_registers:
                raise SyntaxError("exp: syntax error at {}".format(reg))
            register(stream)
        return
    else:
        raise SyntaxError("exp: syntax error at {}".format(stream.pointer().value))

# op : +
#   | -
#   | \*
#   | /
def op(stream):
    if stream.pointer().type in ['PLUS']:
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
    else:
        raise SyntaxError("op: syntax error at {}".format(stream.pointer().value))
    
# register : < a name that starts with 'r' followed by 1 or more digits >
def register(stream):
    if stream.pointer().type in ['REGISTER']:
        stream.match('REGISTER')
        return
    else:
        raise SyntaxError("register: syntax error at {}".format(stream.pointer().value))
    
# number : < any valid integer number>
def number(stream):
    if stream.pointer().type in ['NUMBER']:
        stream.match('NUMBER')
        return


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
            raise SyntaxError("syntax error at {}"
                              .format(token_stream.pointer().value))
    except SyntaxError as e:
        print("error: " + str(e))

if __name__ == "__main__":
    parse()
