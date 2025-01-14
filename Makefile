.PHONY: build dispatch_helper
FLAGS = -Wall -g -Wextra
COMPILER = gcc

build:
	$(COMPILER) $(FLAGS) src/*.c -o tema3 -Iinclude -lm

clean:
	rm -f tema3	

# DO NOT REMOVE THE FOLLOWING RULE:
dispatch_helper:
	@arch=$$(uname -m); \
	os=$$(uname -s); \
	base_dir=$$(pwd); \
	echo "Detected system: OS=$$os, ARCH=$$arch"; \
	if [ "$$os" = "Darwin" ]; then \
	    echo "Darwin is unsupported. Please use Linux VM."; \
	    exit 1; \
	elif [ "$$os" = "Linux" ]; then \
	    if [ "$$arch" = "aarch64" ] || [ "$$arch" = "arm64" ]; then \
	        ln -sf "$$base_dir/checker/helper_linux_arm64.o" "$$base_dir/checker/helper.o"; \
	    elif [ "$$arch" = "x86_64" ]; then \
	        ln -sf "$$base_dir/checker/helper_x86_64.o" "$$base_dir/checker/helper.o"; \
	    else \
	        echo "Unsupported architecture for Linux: $$arch"; \
	        exit 1; \
	    fi; \
	else \
	    echo "Unsupported operating system: $$os"; \
	    exit 1; \
	fi