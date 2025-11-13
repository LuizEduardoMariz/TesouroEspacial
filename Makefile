
TARGET      = tesouro-espacial
SRCDIR      = src
INCDIR      = include
BUILDDIR    = build
ASSETDIR    = assets


SRC         = $(wildcard $(SRCDIR)/*.c)

OBJ         = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRC))


CC          = gcc
CFLAGS      = -I$(INCDIR) -Wall -Wextra -std=c99 -O2


LDFLAGS     = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11


.PHONY: all clean run assets

all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)
	@echo "✅ Build completo: ./$(TARGET)"

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@echo "🎮 Executando $(TARGET)..."
	@./$(TARGET)

clean:
	@rm -rf $(BUILDDIR) $(TARGET)
	@echo "🧹 Projeto limpo!"

assets:
	@mkdir -p $(ASSETDIR)/sounds
	@mkdir -p $(ASSETDIR)/textures
	@mkdir -p $(ASSETDIR)/fonts
	@echo "📁 Pastas de assets criadas com sucesso!"
