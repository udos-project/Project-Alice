#include "gui_element_types.hpp"

namespace ui {

inline message_result greater_result(message_result a, message_result b) {
	if(a == message_result::consumed || b == message_result::consumed)
		return message_result::consumed;
	if(a == message_result::seen || b == message_result::seen)
		return message_result::seen;
	return message_result::unseen;
}


xy_pair child_relative_location(element_base const& parent, element_base const& child) {
	switch(child.base_data.get_orientation()) {
		case orientation::upper_left:
			return xy_pair{ int16_t(child.base_data.position.x), int16_t(child.base_data.position.y) };
		case orientation::upper_right:
			return xy_pair{ int16_t(parent.base_data.size.x + child.base_data.position.x), int16_t(child.base_data.position.y) };
		case orientation::lower_left:
			return xy_pair{ int16_t(child.base_data.position.x), int16_t(parent.base_data.size.y + child.base_data.position.y) };
		case orientation::lower_right:
			return xy_pair{ int16_t(parent.base_data.size.x + child.base_data.position.x), int16_t(parent.base_data.size.y + child.base_data.position.y) };
		case orientation::upper_center:
			return xy_pair{ int16_t(parent.base_data.size.x / 2 + child.base_data.position.x), int16_t(child.base_data.position.y) };
		case orientation::lower_center:
			return xy_pair{ int16_t(parent.base_data.size.x / 2 + child.base_data.position.x), int16_t(parent.base_data.size.y + child.base_data.position.y) };
		case orientation::center:
			return xy_pair{ int16_t(parent.base_data.size.x / 2 + child.base_data.position.x), int16_t(parent.base_data.size.y / 2 + child.base_data.position.y) };
		default:
			return xy_pair{ int16_t(child.base_data.position.x), int16_t(child.base_data.position.y) };
	}
}

element_base* container_base::impl_probe_mouse(sys::state& state, int32_t x, int32_t y) noexcept {
	for(auto& c : children) {
		if(c->is_visible()) {
			auto relative_location = child_relative_location(*this, *c);
			auto res = c->impl_probe_mouse(state, x - relative_location.x, y - relative_location.y);
			if(res)
				return res;
		}
	}
	return element_base::impl_probe_mouse(state, x, y);
}

message_result container_base::impl_on_lbutton_down(sys::state& state, int32_t x, int32_t y, sys::key_modifiers mods) noexcept {
	message_result res = message_result::unseen;
	for(auto& c : children) {
		if(c->is_visible()) {
			auto relative_location = child_relative_location(*this, *c);
			res = greater_result(res, c->impl_on_lbutton_down(state, x - relative_location.x, y - relative_location.y, mods));
			if(res == message_result::consumed)
				return message_result::consumed;
		}
	}
	return greater_result(res, element_base::impl_on_lbutton_down(state, x , y, mods));
}
message_result container_base::impl_on_rbutton_down(sys::state& state, int32_t x, int32_t y, sys::key_modifiers mods) noexcept {
	message_result res = message_result::unseen;
	for(auto& c : children) {
		if(c->is_visible()) {
			auto relative_location = child_relative_location(*this, *c);
			res = greater_result(res, c->impl_on_rbutton_down(state, x - relative_location.x, y - relative_location.y, mods));
			if(res == message_result::consumed)
				return message_result::consumed;
		}
	}
	return greater_result(res, element_base::impl_on_rbutton_down(state, x, y, mods));
}
message_result container_base::impl_on_drag(sys::state& state, int32_t x, int32_t y, sys::key_modifiers mods) noexcept {
	message_result res = message_result::unseen;
	for(auto& c : children) {
		if(c->is_visible()) {
			auto relative_location = child_relative_location(*this, *c);
			res = greater_result(res, c->impl_on_drag(state, x - relative_location.x, y - relative_location.y, mods));
			if(res == message_result::consumed)
				return message_result::consumed;
		}
	}
	return greater_result(res, element_base::impl_on_drag(state, x, y, mods));
}
message_result container_base::impl_on_key_down(sys::state& state, sys::virtual_key key, sys::key_modifiers mods) noexcept {
	message_result res = message_result::unseen;
	for(auto& c : children) {
		if(c->is_visible()) {
			res = greater_result(res, c->impl_on_key_down(state, key, mods));
			if(res == message_result::consumed)
				return message_result::consumed;
		}
	}
	return greater_result(res, element_base::impl_on_key_down(state, key, mods));
}
message_result container_base::impl_on_text(sys::state& state, char ch) noexcept {
	message_result res = message_result::unseen;
	for(auto& c : children) {
		if(c->is_visible()) {
			res = greater_result(res, c->impl_on_text(state, ch));
			if(res == message_result::consumed)
				return message_result::consumed;
		}
	}
	return greater_result(res, element_base::impl_on_text(state, ch));
}
message_result container_base::impl_on_scroll(sys::state& state, int32_t x, int32_t y, float amount, sys::key_modifiers mods) noexcept {
	message_result res = message_result::unseen;
	for(auto& c : children) {
		if(c->is_visible()) {
			auto relative_location = child_relative_location(*this, *c);
			res = greater_result(res, c->impl_on_scroll(state, x - relative_location.x, y - relative_location.y, amount, mods));
			if(res == message_result::consumed)
				return message_result::consumed;
		}
	}
	return greater_result(res, element_base::impl_on_scroll(state, x, y, amount, mods));
}
void container_base::impl_on_update(sys::state& state) noexcept {
	for(auto& c : children) {
		if(c->is_visible()) {
			c->impl_on_update(state);
		}
	}
	on_update(state);
}
message_result container_base::impl_set(Cyto::Any& payload) noexcept {
	message_result res = message_result::unseen;
	for(auto& c : children) {
		res = greater_result(res, c->impl_set(payload));
	}
	return greater_result(res, set(payload));
}

void container_base::impl_render(sys::state& state, int32_t x, int32_t y) noexcept {
	element_base::impl_render(state, x, y);

	for(size_t i = children.size(); i-- > 0; ) {
		if(children[i]->is_visible()) {
			auto relative_location = child_relative_location(*this, *(children[i]));
			children[i]->impl_render(state, x + relative_location.x, y + relative_location.y);
		}
	}
}


std::unique_ptr<element_base> container_base::remove_child(element_base* child) noexcept {
	if(auto it = std::find_if(children.begin(), children.end(),
		[child](std::unique_ptr<element_base>& p) { return p.get() == child; }); it != children.end()) {
		if(it + 1 != children.end())
			std::rotate(it, it + 1, children.end());
		auto temp = std::move(children.back());
		children.pop_back();
		temp->parent = nullptr;
		return temp;
	}
	return std::unique_ptr<element_base>{};
}
void container_base::move_child_to_front(element_base* child) noexcept {
	if(auto it = std::find_if(children.begin(), children.end(),
		[child](std::unique_ptr<element_base>& p) { return p.get() == child; }); it != children.end()) {
		if(it != children.begin())
			std::rotate(children.begin(), it, it + 1);
	}
}
void container_base::move_child_to_back(element_base* child) noexcept {
	if(auto it = std::find_if(children.begin(), children.end(),
		[child](std::unique_ptr<element_base>& p) { return p.get() == child; }); it != children.end()) {
		if(it + 1 != children.end())
			std::rotate(it, it + 1, children.end());
	}
}
void container_base::add_child_to_front(std::unique_ptr<element_base> child) noexcept {
	child->parent = this;
	children.emplace_back(std::move(child));
	if(children.size() > 1) {
		std::rotate(children.begin(), children.end() - 1, children.end());
	}
}
void container_base::add_child_to_back(std::unique_ptr<element_base> child) noexcept {
	child->parent = this;
	children.emplace_back(std::move(child));
}
element_base* container_base::get_child_by_name(sys::state const& state, std::string_view name) noexcept {
	if(auto it = std::find_if(children.begin(), children.end(),
		[&state, name](std::unique_ptr<element_base>& p) { return state.to_string_view(p->base_data.name) == name; }); it != children.end()) {
		return it->get();
	}
	return nullptr;
}
element_base* container_base::get_child_by_index(sys::state const& state, int32_t index) noexcept {
	if(0 <= index && index < int32_t(children.size()))
		return children[index].get();
	return nullptr;
}

ogl::color_modification get_color_modification(bool is_under_mouse, bool is_disabled, bool is_interactable) {
	if(!is_under_mouse || !is_interactable) {
		if(is_disabled) {
			return ogl::color_modification::disabled;
		} else {
			return ogl::color_modification::none;
		}
	} else {
		if(is_disabled) {
			return ogl::color_modification::interactable_disabled;
		} else {
			return ogl::color_modification::interactable;
		}
	}
}

void image_element_base::render(sys::state& state, int32_t x, int32_t y) noexcept {
	dcon::gfx_object_id gid;
	if(base_data.get_element_type() == element_type::image) {
		gid = base_data.data.image.gfx_object;
	} else if(base_data.get_element_type() == element_type::button) {
		gid = base_data.data.button.button_image;
	}
	if(gid) {
		auto& gfx_def = state.ui_defs.gfx[gid];
		if(gfx_def.primary_texture_handle) {
			if(gfx_def.get_object_type() == ui::object_type::bordered_rect) {
				ogl::render_bordered_rect(
					state,
					get_color_modification(this == state.ui_state.under_mouse, disabled, interactable),
					gfx_def.type_dependant,
					float(x), float(y), float(base_data.size.x), float(base_data.size.y),
					ogl::get_texture_handle(state, gfx_def.primary_texture_handle, gfx_def.is_partially_transparent()),
					base_data.get_rotation(),
					gfx_def.is_vertically_flipped()
				);
			} else if(gfx_def.number_of_frames > 1) {
				ogl::render_subsprite(
					state,
					get_color_modification(this == state.ui_state.under_mouse, disabled, interactable),
					frame,
					gfx_def.number_of_frames,
					float(x), float(y), float(base_data.size.x), float(base_data.size.y),
					ogl::get_texture_handle(state, gfx_def.primary_texture_handle, gfx_def.is_partially_transparent()),
					base_data.get_rotation(),
					gfx_def.is_vertically_flipped()
				);
			} else {
				ogl::render_textured_rect(
					state,
					get_color_modification(this == state.ui_state.under_mouse, disabled, interactable),
					float(x), float(y), float(base_data.size.x), float(base_data.size.y),
					ogl::get_texture_handle(state, gfx_def.primary_texture_handle, gfx_def.is_partially_transparent()),
					base_data.get_rotation(),
					gfx_def.is_vertically_flipped()
				);
			}
		}
	}
}

void make_size_from_graphics(sys::state& state, ui::element_data& dat) {
	if(dat.size.x == 0 || dat.size.y == 0) {
		dcon::gfx_object_id gfx_handle;
		float scale = 1.0f;
		if(dat.get_element_type() == ui::element_type::image) {
			gfx_handle = dat.data.image.gfx_object;
			scale = dat.data.image.scale;
		} else if(dat.get_element_type() == ui::element_type::button) {
			gfx_handle = dat.data.button.button_image;
		}
		if(gfx_handle) {
			if(state.ui_defs.gfx[gfx_handle].size.x != 0) {
				dat.size = state.ui_defs.gfx[gfx_handle].size;
			} else {
				auto tex_handle = state.ui_defs.gfx[gfx_handle].primary_texture_handle;
				if(tex_handle) {
					ogl::get_texture_handle(state, tex_handle, state.ui_defs.gfx[gfx_handle].is_partially_transparent());
					dat.size.y = int16_t(state.open_gl.asset_textures[tex_handle].size_y);
					dat.size.x = int16_t(state.open_gl.asset_textures[tex_handle].size_x / state.ui_defs.gfx[gfx_handle].number_of_frames);
				}
			}
			if(scale != 1.0f) {
				dat.size.x = int16_t(dat.size.x * dat.data.image.scale);
				dat.size.y = int16_t(dat.size.y * dat.data.image.scale);
			}
		}
	}
}

std::unique_ptr<element_base> make_element_immediate(sys::state& state, dcon::gui_def_id id) {
	auto& def = state.ui_defs.gui[id];
	if(def.get_element_type() == ui::element_type::image) {
		auto res = std::make_unique<image_element_base>();
		std::memcpy(&(res->base_data), &def, sizeof(ui::element_data));
		make_size_from_graphics(state, res->base_data);
		res->on_create(state);
		return res;
	} else if(def.get_element_type() == ui::element_type::button) {
		auto res = std::make_unique<button_element_base>();
		std::memcpy(&(res->base_data), &def, sizeof(ui::element_data));
		make_size_from_graphics(state, res->base_data);
		res->on_create(state);
		return res;
	} else if(def.get_element_type() == ui::element_type::window) {
		auto res = std::make_unique<window_element_base>();
		std::memcpy(&(res->base_data), &def, sizeof(ui::element_data));
		res->on_create(state);
		return res;
	}
	// TODO: other defaults

	return nullptr;
}

std::unique_ptr<element_base> make_element(sys::state& state, std::string_view name) {
	auto it = state.ui_state.defs_by_name.find(name);
	if(it != state.ui_state.defs_by_name.end()) {
		if(it->second.generator) {
			auto res = it->second.generator(state, it->second.defintion);
			if(res) {
				std::memcpy(&(res->base_data), &(state.ui_defs.gui[it->second.defintion]), sizeof(ui::element_data));
				make_size_from_graphics(state, res->base_data);
				res->on_create(state);
				res->on_update(state);
				return res;
			}
		}
		return make_element_immediate(state, it->second.defintion);
	}
	return std::unique_ptr<element_base>{};
}

state::state() {
	root = std::make_unique<container_base>();
}

void show_main_menu(sys::state& state) {
	if(!state.ui_state.main_menu) {
		auto new_mm = make_element_by_type<window_element_base>(state, "alice_main_menu");
		state.ui_state.main_menu = new_mm.get();
		state.ui_state.root->add_child_to_front(std::move(new_mm));
	} else {
		state.ui_state.main_menu->set_visible(state, true);
		state.ui_state.root->move_child_to_front(state.ui_state.main_menu);
	}
}

}