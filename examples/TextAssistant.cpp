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
String llm_work_id;

void setup()
{
    M5.begin();

#if defined(ENABLE_SD_UPDATER)
    SDU_lobby("TextAssistant");  //-- for SD-Updater ---
#endif

    M5.Display.setTextSize(2);
    M5.Display.setTextScroll(true);

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

    /* Setup LLM module and save returned work id */
    M5.Display.printf(">> Setup llm..\n");
    llm_work_id = module_llm.llm.setup();
}

void loop()
{
    /* Make a question: What is {i} + {i} equal to? */
    static int i = 0;
    i++;
    std::string question = "What is " + std::to_string(i) + " + " + std::to_string(i) + " equal to?";

    M5.Display.setTextColor(TFT_GREEN);
    M5.Display.printf("<< %s\n", question.c_str());
    M5.Display.setTextColor(TFT_YELLOW);
    M5.Display.printf(">> ");

    /* Push question to LLM module and wait inference result */
    module_llm.llm.inferenceAndWaitResult(llm_work_id, question.c_str(), [](String& result) {
        /* Show result on screen */
        M5.Display.printf("%s", result.c_str());
    });

    M5.Display.println();

    delay(500);
}