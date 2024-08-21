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
	@echo "$(GREEN)==============================$(NO_COLOR)"
	@echo "$(GREEN)====   $(GREEN)Running$(GREEN)   ====$(NO_COLOR)"
	@echo "$(GREEN)==============================$(NO_COLOR)\n"
	./build/progr ./data/raw.bin
	@echo "\n$(GREEN)==============================$(NO_COLOR)"
	@echo "$(GREEN)====   $(YELLOW)Completed!$(GREEN)   ====$(NO_COLOR)"
	@echo "$(GREEN)==============================$(NO_COLOR)"

bwasm:
	@echo "$(GREEN)==============================$(NO_COLOR)"
	@echo "$(GREEN)====   $(GREEN)Building Project$(GREEN)   ====$(NO_COLOR)"
	@echo "$(GREEN)==============================$(NO_COLOR)\n"
	bash buildwasm.sh
	@echo "\n$(GREEN)==============================$(NO_COLOR)"
	@echo "$(GREEN)====   $(YELLOW)Build Completed!$(GREEN)   ====$(NO_COLOR)"
	@echo "$(GREEN)==============================$(NO_COLOR)"
