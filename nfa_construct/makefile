#Paths
root := ./src
vpath %.h $(root)
src  := ./src
vpath %.c $(src)
run := toNFA
vpath %.o $(hold_obj)


direct_obj = $(addprefix $(hold_obj)/, $(subst .c,.o, $(direct_src)))
direct_src = $(notdir $(wildcard $(addsuffix /*.c, $(src))))

#Run
hold_obj ?= obj
run ?= run

#Link
$(hold_obj)/%.o: %.c
	@mkdir -p $(hold_obj)
	@$(COMPILE.c) $(OUTPUT_OPTION) $<

$(run): $(direct_obj)
	@$(LINK.c) $^ -o $@
clean:
	@$(RM) -r $(hold_obj)/ *.dot $(run)