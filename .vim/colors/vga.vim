" Vim color file
" Maintainer:  Hussam al-Homsi <sawuare@gmail.com>
" Last Change: 2020 Aug 22

set background=dark

highlight clear
highlight clear Comment
highlight clear Constant
highlight clear Error
highlight clear Identifier
highlight clear Ignore
highlight clear Operator
highlight clear PreProc
highlight clear Special
highlight clear Statement
highlight clear Todo
highlight clear Type
highlight clear Underlined

highlight Comment    guifg=#aaaaaa gui=bold      ctermfg=7 cterm=bold      term=none
highlight Constant   guifg=#aa00aa gui=none      ctermfg=5 cterm=none      term=none
highlight Error      guifg=#aa0000 gui=reverse   ctermfg=1 cterm=reverse   term=reverse
highlight Identifier guifg=#00aaaa gui=none      ctermfg=6 cterm=none      term=none
highlight Ignore     guifg=#000000 gui=none      ctermfg=0 cterm=none      term=none
highlight Operator   guifg=#aa5500 gui=bold      ctermfg=3 cterm=bold      term=none
highlight PreProc    guifg=#0000aa gui=bold      ctermfg=4 cterm=bold      term=none
highlight Special    guifg=#aa00aa gui=bold      ctermfg=5 cterm=bold      term=none
highlight Statement  guifg=#aa5500 gui=bold      ctermfg=3 cterm=none      term=none
highlight Todo       guifg=#aa5500 gui=standout  ctermfg=3 cterm=standout  term=standout
highlight Type       guifg=#00aa00 gui=bold      ctermfg=2 cterm=none      term=none
highlight Underlined guifg=#0000aa gui=underline ctermfg=4 cterm=underline term=underline

let colors_name="vga"
