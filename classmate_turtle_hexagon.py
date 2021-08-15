#!/usr/bin/env python3

## Just got this printed in classmate notebook back.
## Wanted to test the trignometry skills :-P 
## lets try it in python turtle

import turtle
import math

def classmate_hexagon(length):
 draw_hexagon_triangle(length)
 draw_hexagon_triangle(length*2)
 draw_circle(length/2)
 draw_hexagon_circle(length, length/2)
 draw_hexagon_circle(length*2, length/2)

 draw_daimond(length*2)
 draw_another_star(length)

def draw_hexagon_triangle(length):
 turtle.home()

 turn_deg = 60
 for i in range(0,6):
  equilateral_triangle(length)
  turtle.left(turn_deg)

def draw_hexagon_circle(length, radius):
 turtle.penup()
 turtle.forward(length)

 turn_deg = 60
 for i in range(0,6):
  draw_circle(radius)
  turtle.left(120+turn_deg*i)
  turtle.forward(length)

 turtle.penup()
 turtle.setheading(180)
 turtle.forward(length)
 turtle.setheading(0)
  
def equilateral_triangle(side):
 for j in range(0,3):
  turtle.forward(side)
  turtle.left(120)

def draw_circle(radius):
 turtle.setheading(270)
 turtle.penup()
 turtle.forward(radius)
 turtle.setheading(0)
 turtle.pendown()
 turtle.circle(radius)
 turtle.setheading(90)
 turtle.penup()
 turtle.forward(radius)
 turtle.setheading(0)
 turtle.pendown()

def draw_daimond(length):
 turn_deg = 0
 for i in range(0,3):
  turtle.penup()
  turtle.home()
  turtle.setheading(0)
  turtle.left(turn_deg)
  turtle.forward(length)
  turtle.pendown()
  turtle.left(180-30)
  # using pythagoras theorem
  # to find length
  l = 2 * math.sqrt(length**2 - (length/2)**2)
  b = length
  draw_rectangle(l,b)
  turn_deg += 60

def draw_rectangle(l,b):
 for i in range(0,2):
  turtle.forward(l)
  turtle.left(90)
  turtle.forward(b)
  turtle.left(90)

def draw_another_star(length):
 # calculate the length and angle
 # assume that big triangle with sides 2a
 #    A 
 # a /|\
 #  E-F-G
 #a/  |  \
 #B---D---C
 #  a   a
 # 
 # so by pythagoras theorem,
 # AD = sqrt ((2a)**2 - a**2)  = sqrt(3) * a
 # AF = sqrt (a**2 - (a/2)**2) = sqrt(3) * a/2
 # so DF = sqrt(3) * a/2
 # BF = sqrt (DF**2 + BD**2)
 #    = sqrt (7) * a/2
 #
 # angle DBF,
 #    = tan_inverse(FD/BD) 
 #    = (sqrt(3)*a/2)/a
 #    = sqrt(3)/2
 # approximately 40.89 deg
 #
 # angle BFC,
 # BFC = 180 - 2 * DBF,
 # as sum of angles in triangle = 180 and DBF = DCF
 stick_len = (math.sqrt(7) * length)/2  
 turn_deg = math.degrees(math.atan(math.sqrt(3)/2))
 other_turn_deg = (180 - 2*turn_deg)

 ## Damn due to round off issue in,
 ## turn_deg, other_turn_deg and stick_len,
 ## it draws star but its not closed properly
 #turtle.penup()
 #turtle.home()
 #turtle.setheading(0)
 #turtle.forward(length * 2)
 #turtle.pendown()
 #turtle.right(180-turn_deg/2)
 #for i in range (0, 6):
 # turtle.forward(stick_len)
 # turtle.left(180-other_turn_deg)
 # turtle.forward(stick_len)
 # turtle.right(180-turn_deg)

 for hex_deg in range(0,360,60):
  turtle.penup()
  turtle.home()
  turtle.setheading(hex_deg)
  turtle.forward(length*2)
  turtle.pendown()

  turtle.right(180-turn_deg/2)
  turtle.forward(stick_len)
  turtle.back(stick_len)
  turtle.right(turn_deg)
  turtle.forward(stick_len)


## start of main program
if __name__ == "__main__":
 classmate_hexagon(90)
 turtle.exitonclick()

