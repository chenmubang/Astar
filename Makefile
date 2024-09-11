# 原有的 C++ 标志
CXXFLAGS = -Wall -g -I/usr/include/eigen3

# # Python 头文件和库路径
# PYTHON_CFLAGS = -I/usr/include/python3.8 -I/usr/include/python3.8/numpy
# PYTHON_LDFLAGS = $(shell python3-config --ldflags)
# PYTHON_LIBS = -lpython3.8

# 编译目标和依赖关系
Astar:Astar.o
	g++ -o Astar Astar.o

Astar.o: Astar.cpp
	g++ -c Astar.cpp -o Astar.o

# 清理生成文件
clean:
	rm -f *.o Astar 
