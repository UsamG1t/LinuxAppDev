RU = ru/LC_MESSAGES

pkgdata_DATA = $(RU)/$(PACKAGE).mo

$(RU)/$(PACKAGE).mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

$(PACKAGE).pot: ../src/ahello.c
	xgettext -k_ -c $< -o $@

ru.po:	$(PACKAGE).pot
	msgmerge -U $@ $<