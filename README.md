# NLP algorithm C++
applying nlp simple task using C++


##### This was simple NLP algorithm challenge I prefer to do it using C++ The algorithm steps as follows
##### The algorithm steps as follows: 
- Read text data from input file
- Read some keywords splitted by comma from input file
- Randomly insert the keywords several times inside the input text
- Save the occurence of each keyword inside text
- For each two keywords search for the their occurrence together inside defined window size in text
- do the previous step for each pair of keywords
- for each pair of keywords apply the following equation: 
- 2 * occurrence of pair / (occurrence of first word + (occurrence of second word)
- draw a matrix for all pairs with resulted value from previous equation

##### paremeters: 
- window_size: the size of the window to search for occurrence of pairs
- random_times: how many times to insert randomly the keywords inside text
