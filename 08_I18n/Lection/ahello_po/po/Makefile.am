RU = ru/LC_MESSAGES
PACKAGE = ahello

pkgdata_DATA = $(RU)/$(PACKAGE).mo

$(RU)/$(PACKAGE).mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

$(PACKAGE).pot: ../src/$(PACKAGE).c
	xgettext -k_ -c $< -o $@

ru.po:	$(PACKAGE).pot
	msgmerge -U $@ $<
