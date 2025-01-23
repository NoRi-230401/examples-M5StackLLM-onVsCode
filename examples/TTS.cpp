/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include <Arduino.h>
#include <M5Unified.h>
#include <M5ModuleLLM.h>

#if defined(ENABLE_SD_UPDATER)
#include "SDUpdater.h"  //-- for SD-Updater ---
#endif

M5ModuleLLM module_llm;
String tts_work_id;
String language;

void setup()
{
    M5.begin();

#if defined(ENABLE_SD_UPDATER)
    SDU_lobby("TTS");  //-- for SD-Updater ---
#endif

    M5.Display.setTextSize(2);
    M5.Display.setTextScroll(true);
    // M5.Display.setFont(&fonts::efontCN_12);  // Support Chinese display

    language = "en_US";
    // language = "zh_CN";

    /* Init module serial port */
    // int rxd = 16, txd = 17;  // Basic
    // int rxd = 13, txd = 14;  // Core2
    // int rxd = 18, txd = 17;  // CoreS3
    int rxd = M5.getPin(m5::pin_name_t::port_c_rxd);
    int txd = M5.getPin(m5::pin_name_t::port_c_txd);
    Serial2.begin(115200, SERIAL_8N1, rxd, txd);

    /* Init module */
    module_llm.begin(&Serial2);

    /* Make sure module is connected */
    M5.Display.printf(">> Check ModuleLLM connection..\n");
    while (1) {
        if (module_llm.checkConnection()) {
            break;
        }
    }

    /* Reset ModuleLLM */
    M5.Display.printf(">> Reset ModuleLLM..\n");
    module_llm.sys.reset();

    /* Setup Audio module */
    M5.Display.printf(">> Setup audio..\n");
    module_llm.audio.setup();

    /* Setup TTS module and save returned work id */
    M5.Display.printf(">> Setup tts..\n\n");
    m5_module_llm::ApiTtsSetupConfig_t tts_config;
    tts_work_id = module_llm.tts.setup(tts_config, "tts_setup", language);
}

void loop()
{
    /* Make a text for speech: {i} plus {i} equals to {i + i} */
    static int i = 0;
    i++;
    std::string text = std::to_string(i) + " plus " + std::to_string(i) + " equals " + std::to_string(i + i) + ".";
    // std::string text = std::to_string(i) + " 加 " + std::to_string(i) + " 等于 " + std::to_string(i + i) + ".";

    M5.Display.setTextColor(TFT_GREEN);
    M5.Display.printf("<< %s\n\n", text.c_str());

    /* Push text to TTS module and wait inference result */
    module_llm.tts.inference(tts_work_id, text.c_str(), 10000);

    delay(500);
}