const express = require('express');
const axios = require('axios');
const multer = require('multer');
const FormData = require('form-data');
const cors = require('cors'); // Importar o pacote CORS

const app = express();
const port = process.env.PORT || 8080; // Usar a porta 8080 ou a definida no ambiente

// Configuração do multer para upload de arquivos
const upload = multer({ dest: 'uploads/' });

// Habilitar CORS para todas as rotas
app.use(cors());

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(express.static('html'));

// Endpoint para o Spider
app.get('/spider', async (req, res) => {
    try {
        const { url, depth } = req.query;
        const spiderUrl = 'http://spider_container:3000/spider';
        const response = await axios.get(spiderUrl, {
            params: { url, depth }
        });
        res.json(response.data);
    } catch (error) {
        console.error('Error:', error);
        res.status(500).json({ error: 'Error executing spider' });
    }
});

// Endpoint para o Scorpion
app.post('/scorpion', upload.array('files'), async (req, res) => {
    try {
        const { mode, key, value } = req.body;
        const files = req.files;
        const scorpionUrl = 'http://scorpion_container:3000/scorpion';

        const formData = new FormData();
        formData.append('mode', mode);
        formData.append('key', key);
        formData.append('value', value);
        files.forEach(file => {
            formData.append('files', file.path, file.originalname);
        });

        const response = await axios.post(scorpionUrl, formData, {
            headers: formData.getHeaders()
        });

        res.json(response.data);
    } catch (error) {
        console.error('Error:', error);
        res.status(500).json({ error: 'Error executing scorpion' });
    }
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
