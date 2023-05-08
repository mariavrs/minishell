#!/usr/bin/bash 
rm -rf tester/result/bash/*
rm -rf tester/result/minishell/*
rm -rf tester/result/diff/*

if [[ $1 == "clean" ]]
then
	echo -ne '\x1b[33;1mResults removed !\n\x1b[0m'
	exit
fi

if [[ $1 ]]
then
	echo -e '\x1b[35;1m ____ ____ ____ ____ ____ ____ 
||T |||e |||s |||t |||e |||r ||
||__|||__|||__|||__|||__|||__||
|/__\|/__\|/__\|/__\|/__\|/__\|
'
fi

if [[ $1 == "cd" ]] || [[ $1 == "all" ]]
then
	echo -ne '\x1b[33;1mCD : \x1b[0m'
	{
	./tester/tests/cd > tester/result/minishell/cd
	bash tester/tests/cd > tester/result/bash/cd
	diff tester/result/minishell/cd tester/result/bash/cd > tester/result/diff/cd
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5
fi

if [[ $1 == "echo" ]] || [[ $1 == "all" ]]
then
	echo -ne '\x1b[33;1mECHO : '
	{
	./tester/tests/echo > tester/result/minishell/echo
	bash tester/tests/echo > tester/result/bash/echo
	diff tester/result/minishell/echo tester/result/bash/echo > tester/result/diff/echo
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5
fi

if [[ $1 == "env" ]] || [[ $1 == "all" ]]
then
	echo -ne '\x1b[33;1mENV : '
	{
	./tester/tests/env > tester/result/minishell/env
	bash tester/tests/env > tester/result/bash/env
	diff tester/result/minishell/env tester/result/bash/env > tester/result/diff/env
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5
fi

if [[ $1 == "expand" ]] || [[ $1 == "all" ]]
then
	echo -ne '\x1b[33;1mEXPAND : '
	{
	./tester/tests/expand > tester/result/minishell/expand
	bash tester/tests/expand > tester/result/bash/expand
	diff tester/result/minishell/expand tester/result/bash/expand > tester/result/diff/expand
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5
fi

if [[ $1 == "export" ]] || [[ $1 == "all" ]]
then
	echo -ne '\x1b[33;1mEXPORT : '
	{
	./tester/tests/export > tester/result/minishell/export
	bash tester/tests/export > tester/result/bash/export
	diff tester/result/minishell/export tester/result/bash/export > tester/result/diff/export
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5
fi

if [[ $1 == "unset" ]] || [[ $1 == "all" ]]
then
	echo -ne '\x1b[33;1mUNSET : '
	{
	./tester/tests/unset > tester/result/minishell/unset
	bash tester/tests/unset > tester/result/bash/unset
	diff tester/result/minishell/unset tester/result/bash/unset > tester/result/diff/unset
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5
fi

if [[ $1 == "heredoc" ]] || [[ $1 == "all" ]]
then
	echo -ne '\x1b[33;1mHEREDOC : '
	{
	./tester/tests/heredoc > tester/result/minishell/heredoc
	bash tester/tests/heredoc > tester/result/bash/heredoc
	diff tester/result/minishell/heredoc tester/result/bash/heredoc > tester/result/diff/heredoc
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5
fi

if [[ $1 == "pipe" ]] || [[ $1 == "all" ]]
then
	echo -ne '\x1b[33;1mPIPE : '
	{
	./tester/tests/pipe > tester/result/minishell/pipe
	bash tester/tests/pipe > tester/result/bash/pipe
	diff tester/result/minishell/pipe tester/result/bash/pipe > tester/result/diff/pipe
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5
fi

if [[ $1 == "redir" ]] || [[ $1 == "all" ]]
then
	echo -ne '\x1b[33;1mREDIRECTIONS : '
	{
	./tester/tests/redirect > tester/result/minishell/redirect
	bash tester/tests/redirect > tester/result/bash/redirect
	diff tester/result/minishell/redirect tester/result/bash/redirect > tester/result/diff/redirect
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5
fi

if [[ $1 == "extra" ]] || [[ $1 == "all" ]]
then
	echo -ne '\x1b[33;1mEXTRA 1 : '
	{
	./tester/tests/sley > tester/result/minishell/sley
	bash tester/tests/sley > tester/result/bash/sley
	diff tester/result/minishell/sley tester/result/bash/sley > tester/result/diff/sley
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5

	echo -ne '\x1b[33;1mEXTRA 2 : '
	{
	./tester/tests/multi > tester/result/minishell/multi
	bash tester/tests/multi > tester/result/bash/multi
	diff tester/result/minishell/multi tester/result/bash/multi > tester/result/diff/multi
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5

	echo -ne '\x1b[33;1mEXTRA 3 : '
	{
	./tester/tests/line_by_line > tester/result/minishell/line_by_line
	bash tester/tests/line_by_line > tester/result/bash/line_by_line
	diff tester/result/minishell/line_by_line tester/result/bash/line_by_line > tester/result/diff/line_by_line
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5
fi

if [[ $1 == "bonus" ]] || [[ $1 == "all" ]]
then
	echo -ne '\x1b[33;1mBONUS GROUPS : '
	{
	./tester/tests/b_groups > tester/result/minishell/b_groups
	bash tester/tests/b_groups > tester/result/bash/b_groups
	diff tester/result/minishell/b_groups tester/result/bash/b_groups > tester/result/diff/b_groups
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER

	sleep 0.5

	echo -ne '\x1b[33;1mBONUS OPERATORS : '
	{
	./tester/tests/b_operators > tester/result/minishell/b_operators
	bash tester/tests/b_operators > tester/result/bash/b_operators
	diff tester/result/minishell/b_operators tester/result/bash/b_operators > tester/result/diff/b_operators
	} &> /dev/null
	if [[ $? == 0 ]]
	then
		echo -e '\033[32;1mOK\033[0m'
	else
		echo -e "\033[31;1mNOK\033[0m"
	fi
	rm -rf tmp1 tmp2 tmp3 tmp4 tmp5 test1 test2 test3 $USER
fi
