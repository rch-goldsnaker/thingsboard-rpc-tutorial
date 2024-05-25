import axios from "../config/axios.js";

export async function Login() {
  try {
    const username = process.env.TB_USERNAME;
    const password = process.env.TB_PASSWORD;

    if (!username || !password) {
      throw new Error(
        "The environment variables for the username and password are not defined."
      );
    }

    const responseLogin = await axios.post(`/api/auth/login`, {
      username,
      password,
    });

    const { token, refreshToken } = responseLogin.data;
    return { token, refreshToken };
  } catch (error) {
    if (error.response) {
      // The request was made and the server responded with a status code
      // that falls out of the range of 2xx
      console.log(error.response.data);
      console.log(error.response.status);
      console.log(error.response.headers);
    } else if (error.request) {
      // The request was made but no response was received
      // `error.request` is an instance of XMLHttpRequest in the browser and an instance of
      // http.ClientRequest in node.js
      console.log(error.request);
    } else {
      // Something happened in setting up the request that triggered an Error
      console.log("Error", error.message);
    }
    console.log(error.config);
  }
}
