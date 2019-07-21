.PHONY: clean All

All:
	@echo "----------Building project:[ Servitor1D - Debug ]----------"
	@cd "onedee" && "$(MAKE)" -f  "Servitor1D.mk"
clean:
	@echo "----------Cleaning project:[ Servitor1D - Debug ]----------"
	@cd "onedee" && "$(MAKE)" -f  "Servitor1D.mk" clean
