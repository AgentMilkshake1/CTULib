/**   Copyright 2018 Elliot Haisley Brown
 *
 *  Licensed under the (modified) Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      https://github.com/Apache-HB/CTULib/blob/master/LICENSE
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "Meta/Macros.h"
//ALWAYSINLINE

#include "Meta/Aliases.h"
//U32

#pragma once

namespace Cthulhu
{

template<typename> struct Option;
template<typename> struct Array;
template<typename, typename> struct Map;
template<typename, typename> struct Iterator;

/**Dynamically sized string class
 * this class wraps a null terminated char*
 * simmilar to <a href="https://api.unrealengine.com/INT/API/Runtime/Core/Containers/FString/index.html">FString</a> from unreal
 * <a href="https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/-string/index.html">String</a> from kotlin or
 * C#'s <a href="https://docs.microsoft.com/en-us/dotnet/api/system.string?view=netframework-4.7.2">System.String</a>
 */
struct String
{
    String();
    String(char Content);
    String(const char* Content);
    String(const String& Other);

    String& operator=(const String& Other);

    ALWAYSINLINE U32 Len() const;

    ALWAYSINLINE bool IsEmpty() const;
    ALWAYSINLINE operator bool() const;

    bool Equals(const String& Other) const;

    bool operator==(const String& Other) const;
    bool operator!=(const String& Other) const;

    String& operator+=(const String& Other);
    String& operator+=(char Other);

    String operator+(const String& Other) const;
    String operator+(char Other) const;

    String& operator<<(I64 Num);
    String& operator<<(float Num);
    String& operator<<(bool Val);

    void Append(const String& Other);
    void Append(char Other);

    void Push(const String& Other);
    void Push(char Other);

    ALWAYSINLINE char* operator*() const;
    ALWAYSINLINE char* CStr() const;

    bool StartsWith(const String& Pattern) const;
    bool EndsWith(const String& Pattern) const;

    bool ValidIndex(U32 Index) const;

    ALWAYSINLINE char& operator[](U32 Index) const;
    char At(U32 Index) const;

    String SubString(U32 Start, U32 End) const;

    Option<U32> Find(const String& Pattern) const;

    String Upper() const;
    String Lower() const;

    String Trim(const String& Pattern = " ");
    String Replace(const String& Search, const String& Substitute) const;

    String ArrayFormat(const Array<String>& Args) const;
    String Format(const Map<String, String>& Args) const;

    //cut from front
    String& Cut(U32 Amount);

    //drop from back
    String& Drop(U32 Amount);

    bool Has(const String& Pattern) const;
    bool Has(char Item) const;

    Iterator<Array<char>, char> Iterate() const;

    String Reversed() const;

    ALWAYSINLINE ~String();

    //delete the current string and claim a raw pointer as the new string
    void Claim(char* NewData);

private:
    char* Real;
    U32 Length{0};
};

namespace CString
{
    /**
     * @brief Duplicate a string with a new piece of allocated memory
     * 
     * @param Data the string to duplicate
     * @return char* the copies string
     */
    char* Duplicate(const char* Data);
    char* Duplicate(const char* Data, U32 Limit);

    char* Copy(const char* From, char* Into);
    char* Copy(const char* From, char* Into, U32 Limit);

    char* Merge(const char* Left, const char* Right);

    char* Concat(const char* From, char* Into);
    char* Concat(const char* From, char* Into, U32 Limit);

    I32 Compare(const char* Left, const char* Right);
    I32 Compare(const char* Left, const char* Right, U32 Limit);
    
    //strstr
    /**
     * 
     */
    char* Section(char* Haystack, char* Needle);

    /**
     * 
     */
    U32 Length(const char* Content);

    /**
     * 
     */
    char* Reverse(const char* Content);

    /**Faster variants of the standard CString functions
     * 
     */
    namespace Fast
    {
        /** Duplicate a string to a new location in memory
         * @param Data      the string to duplicate
         * @param DataLen   the length of the string
         * @return          the duplicated string
         */
        char* Duplicate(const char* Data, U32 DataLen);
        
        /**
         * 
         */
        char* Section(
            //Haystack string and associated length
            char* Haystack, U32 HaystackLen, 
            //Needle string and associated length
            char* Needle, U32 NeedleLen
        );

        /**
         * 
         */
        char* Reverse(const char* Content, U32 ContentLen);
    }
}

/**
 * @brief 
 * 
 */
namespace Utils
{
    String Padding(const String& Text, U32 Repeat);

    Option<I64> ParseInt(const String& Text);
    Option<I64> ParseBits(const String& Text);
    Option<I64> ParseHex(const String& Text);
    Option<float> ParseFloat(const String& Text);
    Option<bool> ParseBool(const String& Text);

    String ToString(I64 Num);
    String ToString(float Num);
    String ToString(bool Val);

    String HexToString(I64 HexNum);

    String FastToString(float Num);

    ALWAYSINLINE bool IsSpace(char C);
    ALWAYSINLINE bool IsUpper(char C);
    ALWAYSINLINE bool IsLower(char C);
    ALWAYSINLINE bool IsNum(char C);
    ALWAYSINLINE bool IsAlpha(char C);
    ALWAYSINLINE bool IsPrintable(char C);
    ALWAYSINLINE bool IsAlnum(char C);
    ALWAYSINLINE bool IsEOF(char C);
}

/**
 * @brief all constant values or static functions inside of cthulhu
 * 
 */
namespace Consts
{
    /**
     * @brief the platform specific path seperator
     * 
     * @description / on mac or linux and \ on windows
     * 
     * @see OS_WINDOWS
     * @see OS_LINUX
     * @see OS_APPLE
     * 
     * @return const String* the current platforms path seperator
     */
    ALWAYSINLINE const String* PathSeperator();

    /**
     * @brief returns all whitespace characters
     * 
     * @return const String* whitespace characters
     */
    ALWAYSINLINE const String* Whitespace();

    /**
     * @brief returns all uppercase characters
     * 
     * @return const String* all uppercase characters
     */
    ALWAYSINLINE const String* UpperCase();

    /**
     * @brief returns all lowercase characters
     * 
     * @return const String* all lowercase characters
     */
    ALWAYSINLINE const String* LowerCase();

    /**
     * @brief returns all valid characters for a string representation of an octal number
     * 
     * @return const String* all valid octal digits
     */
    ALWAYSINLINE const String* OctDigits();

    /**
     * @brief returns all valid characters for a string representation of a hex number
     * 
     * @return const String* all valid hex digits
     */
    ALWAYSINLINE const String* HexDigits();

    /**
     * @brief return a string containing all number characters
     * 
     * @return const String* all digit characters
     */
    ALWAYSINLINE const String* Digits();

    /**
     * @brief return a string containing every character
     * 
     * @return const String* all characters
     */
    ALWAYSINLINE const String* Chars();
    
    /**
     * @brief return a string of all punctuation characters
     * 
     * @return const String* all punctuation characters
     */
    ALWAYSINLINE const String* Punctuation();

    /**
     * @brief return a string of all printable characters
     * 
     * @return const String* all printable characters
     */
    ALWAYSINLINE const String* Printable();
}

}

