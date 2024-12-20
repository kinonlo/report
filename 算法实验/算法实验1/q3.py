import matplotlib.pyplot as plt
import numpy as np
import math

def midpoint(p1, p2):
    return ((p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2)

def draw_triangle(ax, vertices):
    ax.fill(*zip(*vertices), 'b', alpha=0.5)
    plt.pause(0.2)  

def sierpinski(ax, vertices, depth):
    if depth == 0:
        draw_triangle(ax, vertices)
    else:
        v1, v2, v3 = vertices
        m1 = midpoint(v1, v2)
        m2 = midpoint(v2, v3)
        m3 = midpoint(v1, v3)
        ##分治
        sierpinski(ax, [v1, m1, m3], depth - 1)
        sierpinski(ax, [m1, v2, m2], depth - 1)
        sierpinski(ax, [m3, m2, v3], depth - 1)

def plot_sierpinski_triangle(depth):
    fig, ax = plt.subplots()
    ax.set_aspect('equal', 'box')
    length=2*math.pow(2,depth-1)
    ax.set_xlim(0, length+1)
    ax.set_ylim(0, length*np.sqrt(3)/2+1)
    vertices = [(0, 0), (length, 0), (length/2, length*np.sqrt(3)/2)]
    sierpinski(ax, vertices, depth)
    plt.title("ki")
    plt.axis('off')
    plt.show()
plot_sierpinski_triangle(5) 
