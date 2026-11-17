CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude -pthread

SRC = src/main.cpp \
      src/Utils.cpp \
      src/Pin.cpp \
      src/FeedManager.cpp \
      src/Board.cpp \
      src/Profile.cpp \
      src/InteractionManager.cpp \
      src/PinCreator.cpp \
      src/SearchEngine.cpp \
      src/DatabaseManager.cpp \
      src/NotificationService.cpp \
      src/DataSeeder.cpp \
      src/CLI.cpp \
      src/HttpServer.cpp

TARGET = pixora

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) --server 8080

cli: $(TARGET)
	./$(TARGET) --cli

both: $(TARGET)
	./$(TARGET) --both

clean:
	rm -f $(TARGET)
