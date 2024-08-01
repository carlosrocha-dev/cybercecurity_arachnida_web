# Arachnidia Web - Spider

## Steps to compile and execute

1. Build an Docker image:

```sh
make docker-build
```
2. Start and container with an interactive shell:

```sh
make docker-run
```

3. Run the `spider` in container with of this args `-r, -l [N], -p [path]`, or use all like this example:

```sh
./spider -r -l 3 -p /app/data https://42.fr
```

## LOGS

To after run the `spider`is`t possible to see logs in root dir:

```sh
cat spider.log
```
