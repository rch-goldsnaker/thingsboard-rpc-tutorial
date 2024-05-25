import axios from "axios";
import dotenv from "dotenv";

dotenv.config();

const apiUrl = process.env.TB_API_URL;
const instance = axios.create({
  baseURL: apiUrl,
});

export default instance;
