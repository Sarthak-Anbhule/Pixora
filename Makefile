# PIXORA - Master Makefile
# Builds and runs the C++ Engine (Server & Console Edition)

CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Ibackend/include -pthread

SRC = backend/src/main.cpp \
      backend/src/Utils.cpp \
      backend/src/Pin.cpp \
      backend/src/FeedManager.cpp \
      backend/src/Board.cpp \
      backend/src/Profile.cpp \
      backend/src/InteractionManager.cpp \
      backend/src/PinCreator.cpp \
      backend/src/SearchEngine.cpp \
      backend/src/DatabaseManager.cpp \
      backend/src/NotificationService.cpp \
      backend/src/DataSeeder.cpp \
      backend/src/CLI.cpp \
      backend/src/HttpServer.cpp

TARGET = pixora

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
	@echo "=========================================================="
	@echo "  PIXORA C++ Engine compiled successfully!"
	@echo "  Run Web Server:   ./pixora --server 8080"
	@echo "  Run Terminal CLI: ./pixora --cli"
	@echo "  Run Both:         ./pixora --both"
	@echo "=========================================================="

run: $(TARGET)
	./$(TARGET) --server 8080

cli: $(TARGET)
	./$(TARGET) --cli

both: $(TARGET)
	./$(TARGET) --both

clean:
	rm -f $(TARGET) backend/pixora
