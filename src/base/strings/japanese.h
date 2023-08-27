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

#ifndef MOZC_BASE_STRINGS_JAPANESE_H_
#define MOZC_BASE_STRINGS_JAPANESE_H_

#include <string>
#include <utility>
#include <vector>

#include <string_view>

namespace mozc::japanese {

// Japanese utilities for character form transliteration.
void HiraganaToKatakana(std::string_view input, std::string *output);
std::string HiraganaToKatakana(std::string_view input);

void HiraganaToHalfwidthKatakana(std::string_view input, std::string *output);
std::string HiraganaToHalfwidthKatakana(std::string_view input);

void HiraganaToRomanji(std::string_view input, std::string *output);
std::string HiraganaToRomanji(std::string_view input);

void HalfWidthAsciiToFullWidthAscii(std::string_view input,
                                    std::string *output);
std::string HalfWidthAsciiToFullWidthAscii(std::string_view input);

void FullWidthAsciiToHalfWidthAscii(std::string_view input,
                                    std::string *output);
std::string FullWidthAsciiToHalfWidthAscii(std::string_view input);

void HiraganaToFullwidthRomanji(std::string_view input, std::string *output);
std::string HiraganaToFullwidthRomanji(std::string_view input);

void RomanjiToHiragana(std::string_view input, std::string *output);
std::string RomanjiToHiragana(std::string_view input);

void KatakanaToHiragana(std::string_view input, std::string *output);
std::string KatakanaToHiragana(std::string_view input);

void HalfWidthKatakanaToFullWidthKatakana(std::string_view input,
                                          std::string *output);
std::string HalfWidthKatakanaToFullWidthKatakana(std::string_view input);

void FullWidthKatakanaToHalfWidthKatakana(std::string_view input,
                                          std::string *output);
std::string FullWidthKatakanaToHalfWidthKatakana(std::string_view input);

void FullWidthToHalfWidth(std::string_view input, std::string *output);
std::string FullWidthToHalfWidth(std::string_view input);

void HalfWidthToFullWidth(std::string_view input, std::string *output);
std::string HalfWidthToFullWidth(std::string_view input);

void NormalizeVoicedSoundMark(std::string_view input, std::string *output);
std::string NormalizeVoicedSoundMark(std::string_view input);

// Returns alignment.
std::vector<std::pair<std::string_view, std::string_view>>
AlignRomanjiToHiragana(std::string_view input);

std::vector<std::pair<std::string_view, std::string_view>>
AlignHiraganaToRomanji(std::string_view input);

}  // namespace mozc::japanese

#endif  // MOZC_BASE_STRINGS_JAPANESE_H_
