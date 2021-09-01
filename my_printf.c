  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include <stdarg.h>
  
  int my_putchar(char c) {
      return(write(1, &c, 1)); 
  }
 
 void my_putstr(const char* param_1)
 {
     int i=0;
     while(*param_1){
         my_putchar(*param_1);
         param_1++;
         i++;
     }
 }
  
  char* my_convert(int base, unsigned long num) {
      char* output;
      int last_index = 0;
      if (num == 0) {
          return "0";
      }
  
      char ch;
      unsigned long digit, num_copy = num;
      int size_of_output = 0;
      while (num!=0) {
          num = num / base;
          size_of_output++;
      }
      
      output = (char*)malloc(sizeof(output)*size_of_output);
      last_index = --size_of_output;
      
      while (num_copy != 0) {
          digit = num_copy % base;
          if (digit > 9 && digit < 16 && base == 16) {
              ch = digit + '0' + 7;
          } else {
              ch = digit + '0';
          }
          output[last_index] = ch;
          last_index--;
          num_copy = num_copy / base;
      }
      
      return output;
      free(output);
  }
  
  
  int print_uns_num(unsigned int n)
  {
  	int div=1;
  	int len=0;
  	unsigned int num=n;
  
  	while( num / div > 9){
  		div *= 10;
      }
  	while ( div != 0){
  		len += my_putchar('0' + num / div);
  		num %= div;
  		div /= 10;
  	}
  	return len;
  }
  
  int octal(int num){
      unsigned int value = (unsigned int) num;
      char* ch=(char*)malloc(100*sizeof(char));
      int count=0, ind=0;
  
      if(value==0){
          *ch=48;
          write(1, ch, 1);
          count++;
      }else{
          while(value!=0){
              *ch=48+(value%8);
              value=value/8;
              ch++;
              ind++;
          }
  
          for (int j=0; j<ind; j++){
              ch--;
              write(1, ch, 1);
              count++;
          }
      }
  
      free(ch);
      return count;
  }
  
  int my_printf(char* restrict format, ...) {
      int output = 0;
      char* str;
      unsigned long num_for_case;
      int var;
      char* sample;
      unsigned int v;
  
      
      va_list parameters;
      
      va_start(parameters, format);
      str = format;
      
      while (*str != '\0') {
          if (*str == '%') {
              str++;
              if (*str == 'd') {
                  var = va_arg(parameters, int);
                  if (var < 0) {
                      my_putchar('-');
                      output++;
                      var = -var;
                  }
                  my_putstr(my_convert(10, var));
                  sample = my_convert(10, var);
                  while (*sample != '\0') {
                      output++;
                      sample++;    
                  }
              } else if (*str == 'o') {
                  var = va_arg(parameters, int);
                  octal(var);
              } else if (*str == 'u') {
                  v = va_arg(parameters, int);
                  if (v == 0){
  		            return (print_uns_num(v));
                  }if (v < 1){
                      return (-1);}
                  return (print_uns_num(v));
              }
               else if (*str == 'x') {
                  var = va_arg(parameters, int);
                  if (var < 0) {
                      my_putchar('-');
                      output++;
                      var = -var;
                  }
                  my_putstr(my_convert(16, var));
                  sample = my_convert(16, var);
                  while (*sample != '\0') {
                      output++;
                      sample++;    
                  }
              } else if (*str == 'c') {
                  num_for_case = va_arg(parameters, int);
                  my_putchar(num_for_case);
                  output++;  
              } else if (*str == 's') {
                  sample = va_arg(parameters, char*);
                  if (sample == NULL) {
                      my_putstr("NULL");
                      output += 4;
                  } else {
                      my_putstr(sample);
                      while (*sample != '\0') {
                          output++;
                          sample++;    
                      }
                  }
              } else if (*str == 'p') {
                  num_for_case = (unsigned long)va_arg(parameters, void*);
                  my_putchar('0'); 
                  my_putchar('x');
                  output += 2;
                  my_putstr(my_convert(16, num_for_case));  
                  sample = my_convert(16, num_for_case);
                  while (*sample != '\0') {
                      output++;
                      sample++;    
                  }
              } 
              }else { 
              my_putchar(*str);
              output++;
          }
          str++;
      }
      va_end(parameters);
      
      return output;
  
  }
 
 //testing
  /*
  int main(){
      int a=10; 
      int* ptr =&a;
  
      printf("%s -> %d ->  %p ->  %c ->  %x ->  %o ->  %u ", "Mariya", 34,  ptr, 'K', 17, a, -9);    printf("\n");
      my_printf("%s -> %d ->  %p ->  %c ->  %x ->  %o ->  %u\n", "Mariya", 34, ptr, 'K', 17, a, -9);   printf("\n");
  
      return 0;
  }
 */
