class Stack():
    def __init__(self):
        self.stack = []
    
    def push(self, data):
        self.stack.append(data)
    
    def pop(self):
        if self.isEmpty():
            print("stack is empty")
            return None
        else :
            return self.stack.pop()

    def isEmpty(self):
        if len(self.stack) == 0:
            return True
        return False

    def print(self):
        print(self.stack)

def if_integer(string):
    return string[-1].isdigit()

stack = Stack()

while(True):
    operand = input("<<< ")
    
    if if_integer(operand):
        stack.push(int(operand))
    
    elif operand == "ADD":
        a = stack.pop()
        b = stack.pop()
        stack.push(a+b)
    
    elif operand == "EQUAL":
        a = stack.pop()
        b = stack.pop()
        if(a==b):
            stack.push(True)
        else :
            stack.push(False)

    else:
        print("Invlaid input")

    stack.print()