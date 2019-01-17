# Target : 명령어가 수행되어 나온 결과를 저장할 파일
# Dependency : 목적파일을 만들기 위해 필요한 재료
# Command : 실행 되어야 할 명령어들
# Macro : 코드를 단순화 시키기 위한 방법

CC = gcc	# gcc : GNU compiler collection 사용
CFLAGS = -W -Wall	 # -W : 합법적이지만 모호한 코딩에 대해 붙임
					 # -Wall : 모든 모호한 문법에 대해 경고
					 # 즉 사소한 오류까지 모두 출력한다는 의미
TARGET = diary_exe	# 최종 타겟은 diary_exe

$(TARGET) : memo.o calendar.o main.o	# target filed을 만들기 위해서 memo.o, calendar.o, main.o를 사용하겠다.
	$(CC) $(CFLAGS) -o $(TARGET) memo.o calendar.o main.o	# dependency들을 사용하여 target file을 만들어낸다.

memo.o : memo.c		# memo.c를 사용하여 memo.o를 만들어내겠다.
	$(CC) $(CFLAGS) -c -o memo.o memo.c 	# memo.c를 컴파일하고 memo.o를 만든다.

calendar.o : calendar.c		# calendar.c를 사용하여 calendar.o를 만들어내겠다.
	$(CC) $(CFLAGS) -c -o calendar.o calendar.c		# calendar.c를 컴파일하고 calendar.o를 만든다.

main.o : main.c		# main.c를 사용하여 main.o를 만들어내겠다.
	$(CC) $(CFLAGS) -c -o main.o main.c		# main.c를 컴파일하고 main.o를 만든다.

# make 명령어를 사용하면, 명령어들이 순차적으로 실행되면서 필요한 것들을 만들어내며 최종적으로 타겟파일이 만들어진다.

clean :					# 더미타겟 : 파일을 생성하지 않는 개념적인 타겟
	rm *.o diary_exe 	# make clean 명령어를 사용하면 현제 디렉토리의 모든 .o 파일과 생성된 실행파일을 rm명령어로 제거해준다.
