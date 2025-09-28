# Имя компилятора
GCC = g++

# Флаги компилятора
FLAGS = -Wall -std=c++17

# Флаги для создания .so
SO_FLAGS = -fPIC -shared

# Флаги компоновщика
LDFLAGS = -L. -Wl,-rpath,.
LIBS = -lxor -lpolib -ltritem

# Цель по умолчанию
all: ManyCiphers

# Правило для создания исполняемого файла RGR
ManyCiphers: main.o libpolib.so libtritem.so libxor.so
	$(GCC) $(FLAGS) -o $@ main.o $(LDFLAGS) $(LIBS)

# Правила для создания библиотек
libxor.so: xor.cpp header.h
	$(GCC) $(SO_FLAGS) -o $@ xor.cpp

libtritem.so: tritem.cpp header.h
	$(GCC) $(SO_FLAGS) -o $@ tritem.cpp

libpolib.so: polibius.cpp header.h
	$(GCC) $(SO_FLAGS) -o $@ polibius.cpp

# Правило для компиляции объектных файлов
%.o: %.cpp
	$(GCC) $(FLAGS) -c $< -o $@

# Цель для очистки
clean:
	rm -f *.o *.so RGR
