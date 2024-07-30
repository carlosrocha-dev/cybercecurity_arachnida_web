
# Cybersecurity Arachnida Web

Este projeto inclui dois programas: `spyder` e `scorpion`. O `spyder` é um web scraper, enquanto o `scorpion` manipula metadados Exif em arquivos de imagem.

## Pré-requisitos

- Docker
- Docker Compose

## Limpeza de Contêineres Docker

Para garantir que você está começando com um ambiente limpo, execute os seguintes comandos para parar e remover todos os contêineres, imagens, volumes e redes Docker:

```sh
# Parar todos os contêineres em execução
docker stop $(docker ps -aq)

# Remover todos os contêineres
docker rm $(docker ps -aq)

# Remover todas as imagens
docker rmi $(docker images -q)

# Remover todos os volumes
docker volume rm $(docker volume ls -q)

# Remover todas as redes
docker network rm $(docker network ls -q)
```

**Nota:** Estes comandos são destrutivos e removerão **todos** os recursos Docker do seu sistema.

## Construção do Contêiner Docker

1. **Construir o contêiner**:
    ```sh
    docker-compose build
    ```

2. **Iniciar o contêiner**:
    ```sh
    docker-compose up -d
    ```

## Acessar o Contêiner

Para acessar o contêiner e compilar os projetos `spyder` e `scorpion`:

1. **Acesse o terminal do contêiner**:
    ```sh
    docker exec -it scorpion_spyder_container /bin/bash
    ```

2. **Compile o `spyder`**:
    ```sh
    cd /app/spyder
    make clean
    make
    ```

3. **Compile o `scorpion`**:
    ```sh
    cd /app/scorpion
    make clean
    make
    ```

## Executar o `spyder`

Para executar o programa `spyder` com profundidade de link e URL especificados:

```sh
./spyder -l 3 https://42.fr
```

## Executar o `scorpion`

Para listar, modificar ou deletar metadados Exif em arquivos de imagem:

- **Listar metadados**:
    ```sh
    ./scorpion -l example.jpg
    ```

- **Modificar metadados**:
    ```sh
    ./scorpion -m example.jpg "Exif.Image.Artist" "42"
    ```

- **Deletar metadados**:
    ```sh
    ./scorpion -d example.jpg "Exif.Image.Artist"
    ```

Substitua `example.jpg` pelo caminho real do arquivo de imagem que você deseja processar.

## Limpar o Ambiente Docker

Para parar e remover todos os contêineres, redes e volumes definidos no `docker-compose.yml`:

```sh
docker-compose down --volumes --remove-orphans
```

Para remover todas as imagens construídas pelo `docker-compose`:

```sh
docker-compose down --rmi all
```

## Links

EXIF: https://pt.wikipedia.org/wiki/Exchangeable_image_file_format
