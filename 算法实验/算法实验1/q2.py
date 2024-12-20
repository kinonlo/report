import random
from math import sqrt

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    @staticmethod
    def distance(point1, point2):
        return sqrt((point1.x - point2.x) ** 2 + (point1.y - point2.y) ** 2)
#分治法
def closest_pair(points):
    sorted_points = sorted(points, key=lambda p: p.x)
    return divide_and_conquer(sorted_points)

def divide_and_conquer(sorted_points):
    n = len(sorted_points)
    if n <= 3:
        return brute_force(sorted_points)
    
    mid = n // 2
    left_points = sorted_points[:mid]
    right_points = sorted_points[mid:]

    left_closest = divide_and_conquer(left_points)
    right_closest = divide_and_conquer(right_points)

    min_distance = min(left_closest[2], right_closest[2])


    strip_points = [point for point in sorted_points if abs(point.x - sorted_points[mid].x) < min_distance]
    strip_closest = strip_closest_pair(strip_points, min_distance)

    if strip_closest and strip_closest[2] < min_distance:
        return strip_closest
    elif left_closest[2] < right_closest[2]:
        return left_closest
    else:
        return right_closest

def brute_force(points):
    min_distance = float('inf')
    closest_pair = None
    for i in range(len(points)):
        for j in range(i + 1, len(points)):
            dist = Point.distance(points[i], points[j])
            if dist < min_distance:
                min_distance = dist
                closest_pair = points[i], points[j], dist
    return closest_pair

def strip_closest_pair(strip, min_dist):
    min_distance = min_dist
    closest_pair = None
    strip.sort(key=lambda p: p.y)
    for i in range(len(strip)):
        j = i + 1
        while j < len(strip) and strip[j].y - strip[i].y < min_distance:
            dist = Point.distance(strip[i], strip[j])
            if dist < min_distance:
                min_distance = dist
                closest_pair = strip[i], strip[j], dist
            j += 1
    return closest_pair

points = [Point(random.random() * 100, random.random() * 100) for _ in range(100)]

closest = closest_pair(points)
print("分治法")
print("最小距离:", closest[2])
print("点对坐标1:", closest[1].x, closest[1].y)
print("点对坐标2:", closest[0].x, closest[0].y)
#暴力法
m =points
a=[]
min1=10000000
ans=[0,0]
for i in range(100):
    for k in range(i+1,100):
        temp=Point.distance(m[i],m[k])
        if temp<min1:
            min1=temp
            ans=[i,k]
print()
print("蛮力法")
print("最小距离:",min1)
print("点对坐标1:",m[ans[0]].x,m[ans[0]].y)
print("点对坐标2:",m[ans[1]].x,m[ans[1]].y)
