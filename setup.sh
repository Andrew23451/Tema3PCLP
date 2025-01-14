#!/bin/bash

GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
RED="\033[1;31m"
RESET="\033[0m"

if ! command -v apt-get &> /dev/null; then
    echo -e "${RED}Error: apt-get is not installed or not in the PATH. Please install apt-get to proceed.${RESET}"
    exit 1
fi

check_and_install() {
    package=$1
    echo -e "${BLUE}Checking for ${package}...${RESET}"
    if ! dpkg -l | grep -q "^ii.*${package} "; then
        echo -e "${YELLOW}${package} not found. Installing...${RESET}"
        if ! sudo apt-get install -y "$package"; then
            echo -e "${RED}Error: Failed to install ${package}. Exiting.${RESET}"
            exit 1
        fi
    else
        echo -e "${GREEN}${package} is already installed.${RESET}"
    fi
}

check_python_and_pip() {
    echo -e "${BLUE}Checking for Python and pip...${RESET}"
    if ! command -v python3 &> /dev/null && ! command -v python &> /dev/null; then
        echo -e "${YELLOW}Python is not installed. Installing...${RESET}"
        if ! sudo apt-get install -y python3; then
            echo -e "${RED}Error: Failed to install Python. Exiting.${RESET}"
            exit 1
        fi
    fi

    if ! command -v pip3 &> /dev/null && ! command -v pip &> /dev/null; then
        echo -e "${YELLOW}pip is not installed. Installing...${RESET}"
        if ! sudo apt-get install -y python3-pip; then
            echo -e "${RED}Error: Failed to install pip. Exiting.${RESET}"
            exit 1
        fi
    fi
}

install_cpplint() {
    echo -e "${BLUE}Checking for cpplint...${RESET}"
    if ! pip3 list | grep cpplint && ! pip list | grep cpplint; then
        echo -e "${YELLOW}cpplint not found. Installing...${RESET}"
        if ! pip3 install cpplint --user && ! pip install cpplint --user; then
            echo -e "${RED}Error: Failed to install cpplint. Exiting.${RESET}"
            exit 1
        fi
    else
        echo -e "${GREEN}cpplint is already installed.${RESET}"
    fi
}

echo -e "${GREEN}Updating package lists...${RESET}"
if ! sudo apt-get update; then
    echo -e "${RED}Error: Failed to update package lists. Exiting.${RESET}"
    exit 1
fi

check_and_install "valgrind"
check_and_install "clang"
check_and_install "clang-tidy"
check_python_and_pip
install_cpplint

echo -e "${GREEN}All required packages are installed.${RESET}"
