// Copyright 2010-2021, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "base/strings/japanese.h"

#include <string>
#include <utility>
#include <vector>

#include "base/strings/internal/double_array.h"
#include "base/strings/internal/japanese_rules.h"
#include <string_view>

namespace mozc::japanese {

using ::mozc::japanese::internal::ConvertUsingDoubleArray;

void HiraganaToKatakana(std::string_view input, std::string *output) {
  *output = HiraganaToKatakana(input);
}

std::string HiraganaToKatakana(const std::string_view input) {
  return ConvertUsingDoubleArray(internal::hiragana_to_katakana_da,
                                 internal::hiragana_to_katakana_table, input);
}

void HiraganaToHalfwidthKatakana(std::string_view input, std::string *output) {
  *output = HiraganaToHalfwidthKatakana(input);
}

std::string HiraganaToHalfwidthKatakana(const std::string_view input) {
  // combine two rules
  return FullWidthKatakanaToHalfWidthKatakana(HiraganaToKatakana(input));
}

void HiraganaToRomanji(std::string_view input, std::string *output) {
  *output = HiraganaToRomanji(input);
}

std::string HiraganaToRomanji(const std::string_view input) {
  return ConvertUsingDoubleArray(internal::hiragana_to_romanji_da,
                                 internal::hiragana_to_romanji_table, input);
}

void HalfWidthAsciiToFullWidthAscii(std::string_view input,
                                    std::string *output) {
  *output = HalfWidthAsciiToFullWidthAscii(input);
}

std::string HalfWidthAsciiToFullWidthAscii(const std::string_view input) {
  return ConvertUsingDoubleArray(
      internal::halfwidthascii_to_fullwidthascii_da,
      internal::halfwidthascii_to_fullwidthascii_table, input);
}

void FullWidthAsciiToHalfWidthAscii(std::string_view input,
                                    std::string *output) {
  *output = FullWidthAsciiToHalfWidthAscii(input);
}

std::string FullWidthAsciiToHalfWidthAscii(const std::string_view input) {
  return ConvertUsingDoubleArray(
      internal::fullwidthascii_to_halfwidthascii_da,
      internal::fullwidthascii_to_halfwidthascii_table, input);
}

void HiraganaToFullwidthRomanji(std::string_view input, std::string *output) {
  *output = HiraganaToFullwidthRomanji(input);
}

std::string HiraganaToFullwidthRomanji(const std::string_view input) {
  return HalfWidthAsciiToFullWidthAscii(HiraganaToRomanji(input));
}

void RomanjiToHiragana(std::string_view input, std::string *output) {
  *output = RomanjiToHiragana(input);
}

std::string RomanjiToHiragana(const std::string_view input) {
  return ConvertUsingDoubleArray(internal::romanji_to_hiragana_da,
                                 internal::romanji_to_hiragana_table, input);
}

void KatakanaToHiragana(std::string_view input, std::string *output) {
  *output = KatakanaToHiragana(input);
}

std::string KatakanaToHiragana(std::string_view input) {
  return ConvertUsingDoubleArray(internal::katakana_to_hiragana_da,
                                 internal::katakana_to_hiragana_table, input);
}

void HalfWidthKatakanaToFullWidthKatakana(std::string_view input,
                                          std::string *output) {
  *output = HalfWidthKatakanaToFullWidthKatakana(input);
}

std::string HalfWidthKatakanaToFullWidthKatakana(std::string_view input) {
  return ConvertUsingDoubleArray(
      internal::halfwidthkatakana_to_fullwidthkatakana_da,
      internal::halfwidthkatakana_to_fullwidthkatakana_table, input);
}

void FullWidthKatakanaToHalfWidthKatakana(std::string_view input,
                                          std::string *output) {
  *output = FullWidthKatakanaToHalfWidthKatakana(input);
}

std::string FullWidthKatakanaToHalfWidthKatakana(std::string_view input) {
  return ConvertUsingDoubleArray(
      internal::fullwidthkatakana_to_halfwidthkatakana_da,
      internal::fullwidthkatakana_to_halfwidthkatakana_table, input);
}

void FullWidthToHalfWidth(std::string_view input, std::string *output) {
  *output = FullWidthToHalfWidth(input);
}

std::string FullWidthToHalfWidth(const std::string_view input) {
  return FullWidthKatakanaToHalfWidthKatakana(
      FullWidthAsciiToHalfWidthAscii(input));
}

void HalfWidthToFullWidth(std::string_view input, std::string *output) {
  *output = HalfWidthToFullWidth(input);
}

std::string HalfWidthToFullWidth(const std::string_view input) {
  return HalfWidthKatakanaToFullWidthKatakana(
      HalfWidthAsciiToFullWidthAscii(input));
}

// TODO(tabata): Add another function to split voice mark
// of some UNICODE only characters (required to display
// and commit for old clients)
void NormalizeVoicedSoundMark(std::string_view input, std::string *output) {
  *output = NormalizeVoicedSoundMark(input);
}

std::string NormalizeVoicedSoundMark(const std::string_view input) {
  return ConvertUsingDoubleArray(internal::normalize_voiced_sound_da,
                                 internal::normalize_voiced_sound_table, input);
}

std::vector<std::pair<std::string_view, std::string_view>>
AlignRomanjiToHiragana(std::string_view input) {
  return AlignUsingDoubleArray(internal::romanji_to_hiragana_da,
                               internal::romanji_to_hiragana_table, input);
}

std::vector<std::pair<std::string_view, std::string_view>>
AlignHiraganaToRomanji(std::string_view input) {
  return AlignUsingDoubleArray(internal::hiragana_to_romanji_da,
                               internal::hiragana_to_romanji_table, input);
}

}  // namespace mozc::japanese
