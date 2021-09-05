case $- in
  *i*) ;;
    *) return;;
esac

HISTSIZE="1000"
HISTFILESIZE="2000"
HISTCONTROL="ignoreboth"

shopt -s histappend
shopt -u checkwinsize

if [ -x /usr/bin/tput ] && tput setaf 1 &> /dev/null; then
  PS1="\[\e[33m\]\l \[\e[32m\]\u \[\e[36m\]\h \[\e[34m\]\w \[\e[37m\]\\$ \[\e[39m\]"
else
  PS1="\l \u \h \w \\$ "
fi

if [ -x /usr/bin/dircolors ]; then
  test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"

  alias ls="ls --color=auto"
  alias grep="grep --color=auto"
fi

alias n="nano"
alias v="nano -v"
alias la="ls -A"
alias ll="ls -l"
alias py="python3 -q"

if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi
