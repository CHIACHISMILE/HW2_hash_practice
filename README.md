# HW2_hash_practice
醫工三 b812109032 許家齊 資料結構與演算法 HW2_hash_practice 雜湊練習

# Homework Instructions
附檔資料「hw2_data.txt」是一份近千行的字串資料。每一行只有一個英文字，且文字重複率很高。請寫一隻程式讀進這個檔案，逐行讀進這些英文字，並統計出以下兩點：
 
1. 總共有多少個不重複的英文字
2. 每一個英文字出現次數為和
 
請將作業上傳到github。repository名稱請取為HW2_hash_practice。請以任何你喜歡的方式（WORD/PDF報告、Github Readme，或Jupyter notebook）告訴我程式執行結果。評分點為：
 
1. 是否有正確答出答案
2. 是否能夠清楚看出答案
3. 是否能夠清楚看到程式碼
追加4. 請使用hash or dictionary。我知道有其他更方便的功能，但麻煩請使用hash。
 
加分點：
1. 是否有加註解
2. 程式是否有結構化
3. 變數與function名稱是否清楚可辨識
4. 是否使用github的commit與push上傳程式碼
 
順帶說明一下這個檔案的格式是DOS/Windows，也就是CR+LF做每一行的結尾。雖然理論上不會影響到大部分同學的程式執行，但在Mac/Linux上寫C/C++的同學就需要特別注意一下了。

# Data 
The txt data "hw2_data.txt" must put in the same folder with your code.

# Result
<img width="1503" alt="Screen Shot 2023-03-24 at 3 39 29 PM" src="https://user-images.githubusercontent.com/86188415/227456138-47d2c58f-d31e-40b2-84e4-54c2bb2899fa.png">


# Questions
在將字串轉為hash編碼時，我是將文字的第一個字母轉成ASCII加上第二個字母轉成ASCII...將單字加總完成後再除以hash表的總長度取餘數當作其儲存在hash表中的index值。
神奇的是我有試過若只取第一個字母而已竟然也可以成功分配？！想請問老師可以為我解惑嗎？
