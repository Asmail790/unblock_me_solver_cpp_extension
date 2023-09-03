# description of branch

- Create global memory pool for Block objects since there is less 1000 valid variants and will be initialized much more than 1000 times. 
- Use unordered set of const block pointers. 

Reason: Save memory.