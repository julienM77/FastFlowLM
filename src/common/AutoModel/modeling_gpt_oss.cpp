#include "AutoModel/modeling_gpt_oss.hpp"

GPT_OSS::GPT_OSS(unsigned int device_id) : AutoModel(device_id) {}

void GPT_OSS::load_model(std::string model_path, json model_info, int default_context_length, bool enable_preemption) {
    this->model_path = model_path;
    header_print("FLM", "Loading model: " << this->model_path);
    this->tokenizer = std::make_unique<Tokenizer>(model_path);

    this->setup_tokenizer(model_path);
}

void GPT_OSS::setup_tokenizer(std::string model_path){
    auto tokenizer_config = this->_shared_setup_tokenizer(model_path);
}

std::string GPT_OSS::apply_chat_template(nlohmann::ordered_json& messages) {
    minja::chat_template_inputs inputs;
    inputs.add_generation_prompt = true;
    inputs.messages = messages;
    inputs.extra_context = this->extra_context;
    inputs.extra_context["enable_thinking"] = this->enable_think;
    inputs.extra_context["reasoning_effort"] = this->reasoning_effort;
    inputs.extra_context["model_identity"] = this->model_identity;
    inputs.extra_context["role"] = this->role;

    return this->chat_tmpl->apply(inputs);
}

bool GPT_OSS::insert(chat_meta_info_t& meta_info, lm_uniform_input_t& input)
{
    // preprocess
    this->profiler_list[TKOEN_ENCODE_TIME].start();
    std::string templated_text;
    if (input.messages.empty() && input.prompt.empty()) {
        header_print("WARNING", "No messages or prompt provided");
        return false;
    }
    if (!input.messages.empty()) { // already a formated messages, usually from REST API
        templated_text = this->apply_chat_template(input.messages);
    }
    else if (!input.prompt.empty()) { // a pure text, usually from the cli
        nlohmann::ordered_json messages;

        messages.push_back({ {"role", "user"}, {"content", input.prompt} });
        templated_text = this->apply_chat_template(messages);
    }

    std::vector<int> tokens = this->tokenizer->encode(templated_text);
    this->profiler_list[TKOEN_ENCODE_TIME].stop(tokens.size());
    for (int val : tokens) {
        header_print("NNZZHH", val);
    }
    
}


std::string GPT_OSS::generate(chat_meta_info_t& meta_info, int length_limit, std::ostream& os) {
    std::string a = "nzh";
    return a;
}

std::string GPT_OSS::generate_with_prompt(chat_meta_info_t& meta_info, lm_uniform_input_t& input, int length_limit, std::ostream& os) {
    std::string a = "nzh";
    return a;
}