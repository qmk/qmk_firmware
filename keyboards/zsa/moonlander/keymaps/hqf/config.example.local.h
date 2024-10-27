#pragma once

/**
 * Personal Configuration Template
 * -----------------------------
 * Copy this file to config.local.h and customize with your information.
 * The config.local.h file is git-ignored to protect your personal data.
 */

/**
 * Email Signature Templates
 * -----------------------
 * SIGNATURE_1: Basic signature with name and role
 * SIGNATURE_2: Extended signature including website
 */
#define SIGNATURE_1 SS_TAP(X_ENT) SS_TAP(X_ENT) \
    "John Doe\n" \
    "Senior Developer\n" \
    "Engineering Department"

#define SIGNATURE_2 SS_TAP(X_ENT) SS_TAP(X_ENT) \
    "John Doe\n" \
    "Senior Developer\n" \
    "Engineering Department\n" \
    "https://example.com"

/**
 * Email Address Definitions
 * -----------------------
 * EMAIL_1: Personal email address
 * EMAIL_2: Professional email address
 */
#define EMAIL_1 "john.doe" \
    SS_DOWN(X_RALT) SS_TAP(X_0) SS_UP(X_RALT) \
    "example.com"

#define EMAIL_2 "john.doe" \
    SS_DOWN(X_RALT) SS_TAP(X_0) SS_UP(X_RALT) \
    "company.com"

/**
 * Custom Sound Definition
 * ---------------------
 * Define your own melody using note macros:
 * - B__NOTE: Beat note
 * - W__NOTE: Whole note
 * - H__NOTE: Half note
 */
#define CUSTOM_SOUND \
    B__NOTE(_G6), B__NOTE(_C7), W__NOTE(_G6), \
    H__NOTE(_A6), B__NOTE(_B6), W__NOTE(_E6), \
    W__NOTE(_E6), B__NOTE(_A6), W__NOTE(_G6), \
    H__NOTE(_F6), B__NOTE(_G6), W__NOTE(_C6)

/**
 * Text Templates
 * ------------
 * Predefined text templates for common use
 */
#define TEMPLATE_1 \
    "Dear Team,\n\n" \
    "I hope this email finds you well.\n\n" \
    "Best regards,\n"

#define TEMPLATE_2 \
    "Hi everyone,\n\n" \
    "Quick update on the project status:\n" \
    "- Task 1: Completed\n" \
    "- Task 2: In progress\n\n" \
    "Best regards,"

/**
 * Custom Key Combinations
 * --------------------
 * Define your own keyboard shortcuts
 */
#define CUSTOM_SHORTCUT_1 SS_DOWN(X_LCTL) SS_DOWN(X_LALT) \
    SS_TAP(X_1) SS_UP(X_LALT) SS_