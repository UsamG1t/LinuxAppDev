#!/bin/bash


echo -n "Enter the name of a country: "
read COUNTRY

echo -n "The official language of $COUNTRY is "

case $COUNTRY in

  Lithuania)
    echo -e "Lithuanian\n"
    ;;

  Romania | Moldova)
    echo -e "Romanian\n"
    ;;

  Italy | "San Marino" | Switzerland | "Vatican City")
    echo -e "Italian\n"
    ;;

  *)
    echo -e "unknown\n"
    ;;
esac
