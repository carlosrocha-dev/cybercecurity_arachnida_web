# Dockerfile
FROM debian:latest

# Instalar dependências
RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    libcurl4-openssl-dev \
    libexiv2-dev \
    cmake \
    git

# Copiar os arquivos do projeto para o contêiner
COPY ./spyder /app/spyder
COPY ./scorpion /app/scorpion
COPY ./utils.cpp /app/utils.cpp
COPY ./utils.hpp /app/utils.hpp

WORKDIR /app/spyder
# Limpar e compilar spyder
RUN make clean
RUN make

WORKDIR /app/scorpion
# Limpar e compilar scorpion
RUN make clean
RUN make

# Comando padrão para rodar o contêiner
CMD ["/bin/bash"]
