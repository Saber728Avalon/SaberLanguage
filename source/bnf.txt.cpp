int program (std::vector<LexItem> &list, int n_start) { 
 int i = n_start; 
 i = import_body(list, i); 
 i = program_body(list, i); 
 return i; 
} 




int import_body (std::vector<LexItem> &list, int n_start) { 
 int i = n_start; 
if("struct" != list[i].strInfo) {return i;} 
i++; 
 return i; 
} 




int program_body (std::vector<LexItem> &list, int n_start) { 
 int i = n_start; 
if("xxxx" != list[i].strInfo) {return i;} 
i++; 
 return i; 
} 




