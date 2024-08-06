.PHONY: build

GREEN = \033[0;32m
YELLOW = \033[0;33m
NO_COLOR = \033[0m

build:
	@echo "$(GREEN)==============================$(NO_COLOR)"
	@echo "$(GREEN)====   $(GREEN)Building Project$(GREEN)   ====$(NO_COLOR)"
	@echo "$(GREEN)==============================$(NO_COLOR)\n"
	bash build.sh
	@echo "\n$(GREEN)==============================$(NO_COLOR)"
	@echo "$(GREEN)====   $(YELLOW)Build Completed!$(GREEN)   ====$(NO_COLOR)"
	@echo "$(GREEN)==============================$(NO_COLOR)"

run:
	@echo "Running the program..."
	./progr
