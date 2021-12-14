import sys, os
import time

class Square:

    def __init__(self, x1, y1, x2, y2, d, n, pos):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.d = d
        self.leaf = False
        self.pos = pos
        
        if (n >= self.d):
            self.initGrid(n)
        else:
            self.leaf = True

    def initGrid(self, n):
        w = self.x2 - self.x1
        h = self.y2 - self.y1
        midX = self.x1 + w/2
        midY = self.y1 + h/2
        self.topLeft = Square(self.x1, self.y1, midX, midY, self.d + 1, n, "topLeft")
        self.topRight = Square(midX, midY, self.x2, self.y2, self.d + 1, n, "topRight")
        self.botLeft = Square(self.x1, midY, midX, self.y2, self.d + 1, n, "botLeft")
        self.botRight = Square(midX, midY, self.x2, self.y2, self.d + 1, n, "botRight")

    def getPoint(self, square, x, y):
        #print(square.pos)
        if( square.leaf ):
            return square
        pos = self.getPosFromPoint(square, x, y)
        if ( pos == "topLeft" ):
            self.getPoint(square.topLeft, x, y)
        elif ( pos == "topRight" ):
            self.getPoint(square.topRight, x, y)
        elif ( pos == "botLeft" ):
            self.getPoint(square.botLeft, x, y)
        elif ( pos == "botRight" ):
            self.getPoint(square.botRight, x, y)

    def getPosFromPoint(self, square, x, y):
        w = square.x2 - square.x1
        h = square.y2 - square.y1
        midX = square.x1 + w/2
        midY = square.y1 + h/2

        isTop = False
        isLeft = False
        if ( x < midX ):
            isLeft = True
        if ( y < midY ):
            isTop = True

        if ( isTop and isLeft ):
            return "topLeft"
        elif ( isTop and not isLeft ):
            return "topRight"
        elif ( not isTop and isLeft ):
            return "botLeft"
        elif ( not isTop and not isLeft):
            return "botRight"   

    def getRange( self, square, x1, x2, y1, y2 ):

        if( square.leaf ):
            return square
        pos1 = self.getPosFromPoint(square, x1, y1)
        pos2 = self.getPosFromPoint(square, x2, y2)
        pos3 = self.getPosFromPoint(square, x1, y2)
        pos4 = self.getPosFromPoint(square, x2, y1)

        self.recurseByPos( square, pos1, x1, y1, x2, y2 )
        self.recurseByPos( square, pos2, x1, y1, x2, y2 )
        self.recurseByPos( square, pos3, x1, y1, x2, y2 )
        self.recurseByPos( square, pos4, x1, y1, x2, y2 )



    def recurseByPos( self, square, pos, x1, x2, y1, y2 ):
        if ( pos == "topLeft" ):
            self.getRange(square.topLeft, x1, y1, x2, y2)
        elif ( pos == "topRight" ):
            self.getRange(square.topRight, x1, y1, x2, y2)
        elif ( pos == "botLeft" ):
            self.getRange(square.botLeft, x1, y1, x2, y2)
        elif ( pos == "botRight" ):
            self.getRange(square.botRight, x1, y1, x2, y2)
        


square = Square( 0, 0, 10000, 10000, 1, 7, "Root")
#grid = square.getPoint(square, 7762, 3122)

tic = time.perf_counter()
square.getRange( square, 0, 0, 1920, 1080 )
toc = time.perf_counter()
print(f"{toc - tic:0.8f} seconds")
