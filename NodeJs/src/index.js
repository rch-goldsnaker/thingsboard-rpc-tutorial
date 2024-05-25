import { Login } from "./services/Login.js";
import { RpcServerSide, RpcClientSide } from "./services/Rpc.js";
import dotenv from "dotenv";
dotenv.config();

/// RPC ServerSide ///

async function RpcServer() {
  const deviceId = "2fe83f40-1710-11ef-bf00-a758a0264872";
  const method = "setLedStatus";

  const myObj = {
    method,
    params: 0,
    persistent: true,
    timeout: 5000,
  };

  const resLogin = await Login();
  const requestData = JSON.stringify(myObj);
  const response = await RpcServerSide(deviceId, 'Bearer '+ resLogin.token, requestData);
  console.log(response.data);
}

/// RPC ClientSide ///

async function RpcClient() {
  const accesToken = "zlfeW9lsoRJBb1jTQki3";
  const method = "getCurrentTime";

  const myObj = { method, params: {} };

  const requestData = JSON.stringify(myObj);
  const response = await RpcClientSide(accesToken, requestData);
  console.log(response.data);
}

// RpcClient();
RpcServer();
