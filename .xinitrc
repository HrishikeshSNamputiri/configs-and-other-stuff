[[ -f ~/.Xresources ]] && xrdb -merge -I $HOME ~/.Xresources
~/.fehbg &
picom &
slstatus &
emacs --daemon &
sxhkd &
exec dwm
