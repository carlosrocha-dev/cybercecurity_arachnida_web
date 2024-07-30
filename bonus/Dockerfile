FROM nginx:latest

RUN apt-get update && apt-get install -y nodejs npm

WORKDIR /app

COPY html /usr/share/nginx/html

COPY nginx.conf /etc/nginx/nginx.conf

COPY package*.json ./

RUN npm install

COPY server.js /app/server.js

CMD ["sh", "-c", "node /app/server.js & nginx -g 'daemon off;'"]
