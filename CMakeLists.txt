cmake_minimum_required(VERSION 3.10)
project(AmongUs)

# Inclui automaticamente todos os arquivos .cpp da pasta
file(GLOB_RECURSE SOURCES "*.cpp")

# Comando oficial da Tyra para gerar o ELF de PlayStation 2
add_ps2_executable(amongus ${SOURCES})
