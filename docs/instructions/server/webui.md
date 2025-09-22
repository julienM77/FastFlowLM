---
title: Open WebUI + FLM
nav_order: 2
parent: Local Server (Server Mode)
---

# 📑 Table of Contents

- **[🧩 Run Open WebUI with FastFlowLM](#-run-open-webui-with-fastflowlm)**
- **[🧪 More Examples](#-more-examples)**
  - [Example: Multi Models Comparision Enabled by FLM Queuing](#-example-multi-models-comparision-enabled-by-flm-queuing)
  - [Example: Web Search Integration](#-example-web-search-integration)

---

# 🧩 Run Open WebUI with FastFlowLM

This guide walks you through using `docker-compose.yaml` to run Open WebUI connected to a local FastFlowLM instance on Windows.

---

## ✅ Prerequisites

1. [Docker Desktop for Windows](https://www.docker.com/products/docker-desktop)
   - During installation, enable **WSL2 backend**
   - Reboot if prompted

2. [FastFlowLM](../../install.md)

---

## 📁 Step 1: Create Project Folder

Open PowerShell and run:

```powershell
mkdir open-webui && cd open-webui
```

This creates a clean workspace for your Docker setup.

---

## 📝 Step 2: Create `docker-compose.yaml`

Launch Notepad:

```powershell
notepad docker-compose.yaml
```

Paste the following:

```yaml
services:
  open-webui:
    image: ghcr.io/open-webui/open-webui:main
    container_name: open-webui
    ports:
      - "3000:8080"
    volumes:
      - open-webui-data:/app/backend/data
    environment:
      # Point WebUI to FLM's OpenAI-compatible server
      - OPENAI_API_BASE_URL=http://host.docker.internal:11434/v1
      - OPENAI_API_KEY=dummy-key

      # WebUI settings
      - WEBUI_AUTH=false
      - WEBUI_SECRET_KEY=dummysecretkey
      - ENABLE_TITLE_GENERATION=false
      - ENABLE_FOLLOW_UP_GENERATION=false
      - ENABLE_TAGS_GENERATION=false
      - ENABLE_RETRIEVAL_QUERY_GENERATION=false
      - ENABLE_IMAGE_PROMPT_GENERATION=false
      - ENABLE_WEB_SEARCH=false
      - ENABLE_SEARCH_QUERY_GENERATION=false
    restart: unless-stopped

volumes:
  open-webui-data:
```

---

## ▶️ Step 3: Launch the Open WebUI Container (in PowerShell)

```powershell
docker compose up -d
```
> It could take up to 1 min before you can access Open WebUI.

This starts the container in detached mode.  
You can check logs with:

```powershell
docker logs -f open-webui
```

---

## 🌐 Step 4: Access the WebUI (in Browser)

Open browser and go to:  
**http://localhost:3000**

You should now see the Open WebUI interface.

---

## 🧪 Step 5: Serve FastFlowLM with Model

```powershell
flm serve llama3.2:1b
```

You can now use `FastFlowLM` directly in Open WebUI.
> When switching models, it may take longer time to replace the model in memory.

---

## 🧼 Step 6: Stop or Clean Up (in PowerShell)

```powershell
docker compose stop
```

To **remove** it completely:

```powershell
docker compose down
```

This also removes the container but keeps persistent volume data.

or 

```powershell
docker compose down -v
```

This removes the container and persistent volume data.

---

## 🧼 Step 7: Update Open WebUI

```powershell
docker compose pull
```

---

## 🧠 Notes

- Want login? Set `WEBUI_AUTH=true`
- You must keep FastFlowLM server running
- For persistent chat history, the volume `openwebui-data` stores user data

---

> **Note (When using Open WebUI):**  
> The **Open WebUI** sends multiple background requests to the **server**.  
> To improve stability and performance, you can disable these in **Settings → Chat**:
> - **Title Auto-Generation**
> - **Follow-Up Auto-Generation**
> - **Chat Tags Auto-Generation**
> 
> Toggle them **off**, then refresh the page.

---

# 🧪 More Examples

Well done 🎉 — now let’s explore more apps together!

---

## 🤖 Example: Multi Models Comparision Enabled by FLM Queuing

A step-by-step guide to launching FastFlowLM and interacting with multiple models via Open WebUI.

---

### 🌐 Step 1: Run Open WebUI with FastFlowLM

Follow the quick setup at [here](https://docs.fastflowlm.com/instructions/server/).

---

### 🧩 Step 2:  Select and Add Models

At the top-right corner of the WebUI:

- Choose a model to begin (e.g., `llama3.2:1b`)
- Click **➕** to add other models, e.g.:
	- `qwen3:0.6b`
	- `gemma3:1b`

	You’ll now see several models listed. That means each one can answer your prompt.

---

### 💬 Step 3: Interact with Models

Type anything you're curious about in the input box.

⚠️ Please note:

- Each model will reply in sequences (not all at once)..
- The flm server dynamically loads each model based on your selection.

---

### 🎯 Step 4: Select or Merge

After receiving replies from multiple models, choose how you'd like to continue:

- ✅ **Use the Best Response**  
  Select the answer that best meets your expectations. That response will become the active context for your next question.

- 🔗 **Merge All Responses**  
  Combine insights from all models and continue the conversation using your preferred model. This lets you synthesize multiple perspectives into a unified thread.

---

## 🌐 Example: Web Search Integration

Step-by-step guide to powering Agentic AI web search in Open WebUI — NPU-only, lightning-fast, with Google PSE + FLM.

---

### 🛠️ Step 1: Set Up Google PSE

1. Go to [Google Programmable Search Engine](https://developers.google.com/custom-search) and sign in or create an account. Click `create a search engine`. Review the *Overview* page.
2. Visit the [Control Panel](https://programmablesearchengine.google.com/controlpanel/all) and click the `Add` button.
3. Fill in:
	- A **name** for your search engine (e.g., flm-search)
	- **What to search?** (e.g., select `Search the entire web`)
	- **Search settings** (e.g., enable `Image search`)
	- Verify you’re not a robot
	- Then click **`Create`**
4. After creation, click **`Customize`**.
5. Copy and save your **Search Engine ID** (you’ll need it later).
6. Scroll down to **Programmatic Access** → click **Get started**.
7. Find **Programmable Search Engine (free edition) users** → click **Get a Key**.
8. Select `Create a project` → Enter new project name (e.g., owbui-search) → click next → click `SHOW KEY` to reveal your **API key** → copy and save it (you'll need it later).

---

### 🌐 Step 2: Run Open WebUI with FastFlowLM

Follow the quick setup guide **[here](#-example-multi-models-comparison-enabled-by-flm-queuing-v0910-or-beyond)**.

---
### 🧩 Step 3: Enable Web Search in Open WebUI

With your **API Key** and **Search Engine ID** from Step 1, follow these steps:

1. In the **bottom-left corner**, click **`User`** icon, then select **`Settings`**.
2. In the **bottom panel**, open **`Admin Settings`**.
3. From the **left sidebar**, click **`Web Search`**.
4. Under `General`, toggle **`Web Search`** to enable web search function.
5. Set **`Web Search Engine`** as **`google_pse`**.
6. Enter your saved:
    - **Google PSE API Key**
    - **Google PSE Engine ID**
7. Under `Loader`, set `Concurrent Requests` to 10 or more (optional).
8. Click **`Save`**.

---

### 💬 Step 4: Start Using Web Search

1. Start a new chat and select your preferred model (e.g., qwen3-tk:4b).
> ⚠️ **Note:** not all models handle web search well.
2. Under the chat input box, Click `integrations`, and toggle **Web Search** to activate it .
- 🔄 You’ll need to activate this **every time you start a new chat**. 
3. Ask anything you're curious about—real-time search will enhance your answers!

---