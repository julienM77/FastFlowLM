#pragma once

#include "AutoModel/automodel.hpp"

class GPT_OSS : public AutoModel {
private:
    std::string current_model = "gpt-oss";

    bool enable_think = true;

    std::string reasoning_effort = "high";
    std::string model_identity = "You are ChatGPT, a large language model trained by OpenAI.";
    std::string role = "developer";

    void setup_tokenizer(std::string model_path);
public:
    GPT_OSS(unsigned int device_id);

    void load_model(std::string model_path, json model_info, int default_context_length = -1, bool enable_preemption = false) override;
    std::string apply_chat_template(nlohmann::ordered_json& messages) override;
    bool insert(chat_meta_info_t& meta_info, lm_uniform_input_t& input) override;
    std::string generate(chat_meta_info_t& meta_info, int length_limit, std::ostream& os) override;
    std::string generate_with_prompt(chat_meta_info_t& meta_info, lm_uniform_input_t& input, int length_limit, std::ostream& os = std::cout) override;
};