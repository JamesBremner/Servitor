.PHONY: clean All

All:
	@echo "----------Building project:[ Servitor3D - Debug ]----------"
	@cd "threedee" && "$(MAKE)" -f  "Servitor3D.mk"
clean:
	@echo "----------Cleaning project:[ Servitor3D - Debug ]----------"
	@cd "threedee" && "$(MAKE)" -f  "Servitor3D.mk" clean
